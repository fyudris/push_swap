#!/bin/bash

# --- Configuration ---
PUSH_SWAP_EXEC=".././push_swap"     # Path to your push_swap executable
CHECKER_EXEC=".././checker_linux"   # Path to your checker executable
NUM_TEST_RUNS=5                     # Number of times to run each test size
DEFAULT_MIN_VAL=-10000
DEFAULT_MAX_VAL=10000
LOG_DIR="./benchmark_logs"          # Directory to store log files

# Define operation limits (adjust if needed)
LIMIT_100_OPS_TARGET=700
LIMIT_500_OPS_TARGET=5500

# --- Colors ---
RED='\033[0;31m'
GREEN='\033[0;32m'
YELLOW='\033[0;33m'
BLUE='\033[0;34m'
NC='\033[0m' # No Color

# --- Setup Log Directory ---
mkdir -p "$LOG_DIR"
echo -e "${BLUE}Log files will be stored in '$LOG_DIR'${NC}"

# --- Prerequisite Checks ---
# (Same as previous version - checking for PUSH_SWAP_EXEC and CHECKER_EXEC)
echo -e "${BLUE}Checking for necessary executables...${NC}"
if [ ! -f "$PUSH_SWAP_EXEC" ] || [ ! -x "$PUSH_SWAP_EXEC" ]; then
    echo -e "${RED}Error: '$PUSH_SWAP_EXEC' not found or not executable. Please check the path.${NC}"
    exit 1
fi
echo -e "${GREEN}Found '$PUSH_SWAP_EXEC'.${NC}"

if [ ! -f "$CHECKER_EXEC" ] || [ ! -x "$CHECKER_EXEC" ]; then
    echo -e "${YELLOW}Warning: '$CHECKER_EXEC' not found or not executable. Correctness checks will be skipped.${NC}"
    SKIP_CHECKER=true
else
    echo -e "${GREEN}Found '$CHECKER_EXEC'.${NC}"
    SKIP_CHECKER=false
fi
echo "--------------------------------------"
# Clear/Create Log files for this session
> "$LOG_DIR/log_100_success.txt"
> "$LOG_DIR/log_100_fail.txt"
> "$LOG_DIR/log_500_success.txt"
> "$LOG_DIR/log_500_fail.txt"
> "$LOG_DIR/all_runs_summary.txt"


# --- Helper Functions ---
generate_random_numbers() {
    local count=$1
    local min_val=$2
    local max_val=$3
    local error_file="/tmp/gen_num_error.txt"
    rm "$error_file" 2>/dev/null

    if [ -z "$count" ] || [ -z "$min_val" ] || [ -z "$max_val" ]; then return 1; fi
    if [ "${min_val}" -gt "${max_val}" ]; then return 1; fi

    seq "${min_val}" "${max_val}" 2>>"$error_file" | shuf -n "${count}" 2>>"$error_file" | tr '\n' ' ' | sed 's/ $//'
    local success_code=$?

    if [ -s "$error_file" ] || [ $success_code -ne 0 ]; then
        # echo -e "${RED}DEBUG GenNum Error: $(cat $error_file)${NC}" # Uncomment for debugging
        return 1
    fi
    return 0
}

run_test() {
    local number_count=$1
    local operation_limit=$2
    local test_label="$3"
    local total_ops_for_avg=0
    local successful_runs=0
    local failed_runs=0
    local min_ops_this_set="N/A"
    local max_ops_this_set="N/A"

    local log_success_file="$LOG_DIR/log_${number_count}_success.txt"
    local log_fail_file="$LOG_DIR/log_${number_count}_fail.txt"

    echo -e "\n${BLUE}--- ${test_label} (Target: < ${operation_limit} ops) ---${NC}" | tee -a "$LOG_DIR/all_runs_summary.txt"

    for i in $(seq 1 $NUM_TEST_RUNS); do
        current_run_log_prefix="Run $i/$NUM_TEST_RUNS for ${number_count} numbers"
        echo -n "  $current_run_log_prefix: "

        local random_args
        random_args=$(generate_random_numbers "${number_count}" "${DEFAULT_MIN_VAL}" "${DEFAULT_MAX_VAL}")
        local gen_exit_code=$?

        if [ $gen_exit_code -ne 0 ] || [ -z "$random_args" ]; then
            local fail_msg="${RED}FAIL (Could not generate random numbers.)${NC}"
            echo -e "$fail_msg"
            echo "$current_run_log_prefix: Random number generation failed." >> "$log_fail_file"
            echo "$current_run_log_prefix: Random number generation failed." >> "$LOG_DIR/all_runs_summary.txt"
            failed_runs=$((failed_runs + 1))
            continue
        fi

        local operations_output
        local push_swap_exit_code
        operations_output=$($PUSH_SWAP_EXEC $random_args 2>&1)
        push_swap_exit_code=$?

        if [ $push_swap_exit_code -ne 0 ] || echo "$operations_output" | grep -q "Error"; then
             local fail_msg="${RED}FAIL (Push_swap error/exit)${NC}"
             echo -e "$fail_msg"
             echo "$current_run_log_prefix: Push_swap error. Input: $random_args | Output: $operations_output" >> "$log_fail_file"
             echo "$current_run_log_prefix: Push_swap error. Input: $random_args" >> "$LOG_DIR/all_runs_summary.txt"
             failed_runs=$((failed_runs + 1))
             continue
        fi

        local num_ops=$(echo "$operations_output" | wc -l | awk '{print $1}')
        local checker_output_text="SKIPPED"
        local checker_verdict="OK"

        if [ "$SKIP_CHECKER" = false ]; then
            checker_output_text=$(echo "$operations_output" | $CHECKER_EXEC $random_args 2>&1)
            if [[ "$checker_output_text" == "OK" ]]; then
                checker_verdict="OK"
            else
                checker_verdict="KO"
            fi
        fi

        local run_summary_line="$current_run_log_prefix | Input: $random_args | Ops: $num_ops | Checker: $checker_output_text"

        if [ "$checker_verdict" = "OK" ]; then
            if [ "$num_ops" -lt "$operation_limit" ]; then
                echo -e "${GREEN}PASS${NC} (${num_ops} ops)"
                echo "PASS | $run_summary_line" >> "$log_success_file"
                echo "  $current_run_log_prefix: PASS (${num_ops} ops)" >> "$LOG_DIR/all_runs_summary.txt"
                total_ops_for_avg=$((total_ops_for_avg + num_ops))
                successful_runs=$((successful_runs + 1))
                if [ "$min_ops_this_set" = "N/A" ] || [ "$num_ops" -lt "$min_ops_this_set" ]; then min_ops_this_set=$num_ops; fi
                if [ "$max_ops_this_set" = "N/A" ] || [ "$num_ops" -gt "$max_ops_this_set" ]; then max_ops_this_set=$num_ops; fi
            else
                echo -e "${YELLOW}FAIL (Ops Limit Exceeded: ${num_ops})${NC}"
                echo "FAIL (Ops Limit) | $run_summary_line" >> "$log_fail_file"
                echo "  $current_run_log_prefix: FAIL (Ops Limit Exceeded: ${num_ops} ops)" >> "$LOG_DIR/all_runs_summary.txt"
                failed_runs=$((failed_runs + 1))
            fi
        else
            echo -e "${RED}FAIL (Checker: ${checker_output_text})${NC}"
            echo "FAIL (Checker KO) | $run_summary_line" >> "$log_fail_file"
            echo "  $current_run_log_prefix: FAIL (Checker: ${checker_output_text})" >> "$LOG_DIR/all_runs_summary.txt"
            failed_runs=$((failed_runs + 1))
        fi
    done

    summary_output="  ${BLUE}Summary for ${number_count} numbers:${NC}\n"
    if [ "$successful_runs" -gt 0 ]; then
        local avg_ops=$((total_ops_for_avg / successful_runs))
        summary_output+="    Successful runs: ${GREEN}${successful_runs}/${NUM_TEST_RUNS}${NC}\n"
        summary_output+="    Avg ops (successful): ${GREEN}${avg_ops}${NC}\n"
        summary_output+="    Min ops (successful): ${GREEN}${min_ops_this_set}${NC}\n"
        summary_output+="    Max ops (successful): ${GREEN}${max_ops_this_set}${NC}\n"
    else
        summary_output+="    Successful runs: ${RED}${successful_runs}/${NUM_TEST_RUNS}${NC}\n"
    fi
    if [ "$failed_runs" -gt 0 ]; then
        summary_output+="    Failed runs: ${RED}${failed_runs}/${NUM_TEST_RUNS}${NC}"
    fi
    summary_output+="--------------------------------------"
    echo -e "$summary_output" | tee -a "$LOG_DIR/all_runs_summary.txt"


    if [ "$failed_runs" -gt 0 ]; then return 1; fi
    return 0
}

# --- Main Script ---
# (Same structure as before, calling run_test and printing final summary)
rm /tmp/gen_num_error.txt 2>/dev/null # Clean up any old error file

echo -e "\n${BLUE} Initiating Push_swap Benchmark Suite ${NC}" | tee -a "$LOG_DIR/all_runs_summary.txt"
echo "======================================" | tee -a "$LOG_DIR/all_runs_summary.txt"

run_test 100 $LIMIT_100_OPS_TARGET "Benchmark: 100 Random Numbers"
test_100_status=$?

run_test 500 $LIMIT_500_OPS_TARGET "Benchmark: 500 Random Numbers"
test_500_status=$?

echo -e "\n${BLUE} Benchmark Suite Finished. ${NC}" | tee -a "$LOG_DIR/all_runs_summary.txt"
echo "======================================" | tee -a "$LOG_DIR/all_runs_summary.txt"

final_status_message=""
all_passed=true

if [ "$test_100_status" -eq 0 ]; then
    final_status_message+="${GREEN}[PASS]${NC} 100 Numbers Benchmark (Target: <$LIMIT_100_OPS_TARGET ops)\n"
else
    final_status_message+="${RED}[FAIL]${NC} 100 Numbers Benchmark (Target: <$LIMIT_100_OPS_TARGET ops)\n"
    all_passed=false
fi

if [ "$test_500_status" -eq 0 ]; then
    final_status_message+="${GREEN}[PASS]${NC} 500 Numbers Benchmark (Target: <$LIMIT_500_OPS_TARGET ops)\n"
else
    final_status_message+="${RED}[FAIL]${NC} 500 Numbers Benchmark (Target: <$LIMIT_500_OPS_TARGET ops)\n"
    all_passed=false
fi

echo -e "Final Summary:\n$(echo -e "$final_status_message")" | tee -a "$LOG_DIR/all_runs_summary.txt"

if [ "$all_passed" = true ]; then
    echo -e "${GREEN}Congratulations! All primary benchmarks passed meeting the 100% validation targets.${NC}" | tee -a "$LOG_DIR/all_runs_summary.txt"
else
    echo -e "${RED}One or more primary benchmarks did not consistently pass. Review failed tests and logs in '$LOG_DIR'.${NC}" | tee -a "$LOG_DIR/all_runs_summary.txt"
fi
echo "======================================" | tee -a "$LOG_DIR/all_runs_summary.txt"

rm /tmp/gen_num_error.txt 2>/dev/null # Final cleanup

exit 0
