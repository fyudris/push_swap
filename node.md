 gdb ./push_swap
GNU gdb (Ubuntu 12.1-0ubuntu1~22.04.2) 12.1
Copyright (C) 2022 Free Software Foundation, Inc.
License GPLv3+: GNU GPL version 3 or later <http://gnu.org/licenses/gpl.html>
This is free software: you are free to change and redistribute it.
There is NO WARRANTY, to the extent permitted by law.
Type "show copying" and "show warranty" for details.
This GDB was configured as "x86_64-linux-gnu".
Type "show configuration" for configuration details.
For bug reporting instructions, please see:
<https://www.gnu.org/software/gdb/bugs/>.
Find the GDB manual and other documentation resources online at:
    <http://www.gnu.org/software/gdb/documentation/>.

For help, type "help".
Type "apropos word" to search for commands related to "word"...
Reading symbols from ./push_swap...
(gdb) r
Starting program: /home/fyudris/Documents/42_github/Rank_02/push_swap/push_swap
[Thread debugging using libthread_db enabled]
Using host libthread_db library "/lib/x86_64-linux-gnu/libthread_db.so.1".
[Inferior 1 (process 338935) exited with code 01]
(gdb) q

╭─    ~/Documents/42_github/Rank_02/push_swap    master ?4 ······················································· ✔  5s   1.05   92%   9.72G   18:28:01 
╰─ gdb --args ./push_swap `shuf -i 0-99 -n 10`
GNU gdb (Ubuntu 12.1-0ubuntu1~22.04.2) 12.1
Copyright (C) 2022 Free Software Foundation, Inc.
License GPLv3+: GNU GPL version 3 or later <http://gnu.org/licenses/gpl.html>
This is free software: you are free to change and redistribute it.
There is NO WARRANTY, to the extent permitted by law.
Type "show copying" and "show warranty" for details.
This GDB was configured as "x86_64-linux-gnu".
Type "show configuration" for configuration details.
For bug reporting instructions, please see:
<https://www.gnu.org/software/gdb/bugs/>.
Find the GDB manual and other documentation resources online at:
    <http://www.gnu.org/software/gdb/documentation/>.

For help, type "help".
Type "apropos word" to search for commands related to "word"...
Reading symbols from ./push_swap...
(gdb) r
Starting program: /home/fyudris/Documents/42_github/Rank_02/push_swap/push_swap 55 48 85 54 96 62 67 11 59 43
[Thread debugging using libthread_db enabled]
Using host libthread_db library "/lib/x86_64-linux-gnu/libthread_db.so.1".

Program received signal SIGSEGV, Segmentation fault.
push_cheapest_a_to_b (a=0x7fffffffdb68, b=0x7fffffffdb60) at src/operations/sort_controller.c:63
63			&& cheapest_node->target_node->above_median)
(gdb) list
58	{
59		t_stack_node	*cheapest_node;
60
61		cheapest_node = get_cheapest_node(*a);
62		if (cheapest_node->above_median
63			&& cheapest_node->target_node->above_median)
64			rotate_both_for_push(a, b, cheapest_node);
65		else if (!(cheapest_node->above_median)
66			&& !(cheapest_node->target_node->above_median))
67			reverse_rotate_both_for_push(a, b, cheapest_node);
(gdb) p a
$1 = (t_stack_node **) 0x7fffffffdb68
(gdb) p *a
$2 = (t_stack_node *) 0x4072a0
(gdb) p **a
$3 = {value = 55, index = 0, push_cost = 0, above_median = false, cheapest = false, target_node = 0x0, next = 0x4072d0, prev = 0x0}
(gdb) p **b
Cannot access memory at address 0x0
(gdb) p *b
$4 = (t_stack_node *) 0x0
(gdb) p b
$5 = (t_stack_node **) 0x7fffffffdb60
(gdb) up
#1  0x000000000040280e in perform_push_swap_sort (a=0x7fffffffdb68, b=0x7fffffffdb60) at src/operations/sort_controller.c:115
115				push_cheapest_a_to_b(a, b);
(gdb) list
110
111		len_a = stack_size(*a);
112		if (len_a-- > 3 && !is_stack_sorted(*a))
113		{
114			while (len_a-- > 3)
115				push_cheapest_a_to_b(a, b);
116			sort_three(a);
117		}
118		while (*b)
119		{
(gdb) up
#2  0x000000000040124e in main (argc=11, argv=0x7fffffffdc98) at src/push_swap.c:34
34				perform_push_swap_sort(&a, &b);
(gdb) down
#1  0x000000000040280e in perform_push_swap_sort (a=0x7fffffffdb68, b=0x7fffffffdb60) at src/operations/sort_controller.c:115
115				push_cheapest_a_to_b(a, b);
(gdb) down
#0  push_cheapest_a_to_b (a=0x7fffffffdb68, b=0x7fffffffdb60) at src/operations/sort_controller.c:63
63			&& cheapest_node->target_node->above_median)
(gdb) list
58	{
59		t_stack_node	*cheapest_node;
60
61		cheapest_node = get_cheapest_node(*a);
62		if (cheapest_node->above_median
63			&& cheapest_node->target_node->above_median)
64			rotate_both_for_push(a, b, cheapest_node);
65		else if (!(cheapest_node->above_median)
66			&& !(cheapest_node->target_node->above_median))
67			reverse_rotate_both_for_push(a, b, cheapest_node);
(gdb) q
A debugging session is active.

	Inferior 1 [process 339147] will be killed.

Quit anyway? (y or n) y

╭─    ~/Documents/42_github/Rank_02/push_swap    master ?4 ··················································· ✔  3m 49s   0.57   92%   9.71G   18:32:08 
╰─ shuf -i 0-99 -n 10
88
25
95
2
80
49
30
18
31
5

╭─    ~/Documents/42_github/Rank_02/push_swap    master ?4 ······························································ ✔  0.59   92%   9.71G   18:32:20 
╰─ shuf -i 0-5 -n 10
2
0
3
5
1
4

