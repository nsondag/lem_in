-----
60
##end
1 7 9
##start
0 9 3
2 5 4
3 12 45
4 84 34
5 46 25
6 56 46
7 5 5
8 651 15
9 456 41
10 4561 4156
11 415 123
12 784 12
0-8
8-9
9-10
10-11
11-12
12-1
0-5
5-6
6-7
7-1
0-2
2-3
3-4
4-1
-----
-- d1 0: 0
-- d1 1: 4
-- d1 2: 1
-- d1 3: 2
-- d1 4: 3
-- d1 5: 1
-- d1 6: 2
-- d1 7: 3
-- d1 8: 1
-- d1 9: 2
-- d1 10: 3
-- d1 11: 4
-- d1 12: 5
ici 0.000044
-- nb_tubes 0 : 3 --
-- dest  8: len  1
-- dest  5: len  1
-- dest  2: len  1

-- nb_tubes 1 : 3 --
-- dest 12: len  1
-- dest  7: len  1
-- dest  4: len  1

-- nb_tubes 2 : 2 --
-- dest  0: len  1
-- dest  3: len  1

-- nb_tubes 3 : 2 --
-- dest  2: len  1
-- dest  4: len  1

-- nb_tubes 4 : 2 --
-- dest  3: len  1
-- dest  1: len  1

-- nb_tubes 5 : 2 --
-- dest  0: len  1
-- dest  6: len  1

-- nb_tubes 6 : 2 --
-- dest  5: len  1
-- dest  7: len  1

-- nb_tubes 7 : 2 --
-- dest  6: len  1
-- dest  1: len  1

-- nb_tubes 8 : 2 --
-- dest  0: len  1
-- dest  9: len  1

-- nb_tubes 9 : 2 --
-- dest  8: len  1
-- dest 10: len  1

-- nb_tubes 10 : 2 --
-- dest  9: len  1
-- dest 11: len  1

-- nb_tubes 11 : 2 --
-- dest 10: len  1
-- dest 12: len  1

-- nb_tubes 12 : 2 --
-- dest 11: len  1
-- dest  1: len  1

---after_modif---
-- 0 --
-- dest  8: tmp_len  0: tree  1
-- dest  5: tmp_len  0: tree  1
-- dest  2: tmp_len  0: tree  1

-- 1 --
-- dest 12: tmp_len  0: tree  1
-- dest  7: tmp_len  2: tree  0
-- dest  4: tmp_len  2: tree  0

-- 2 --
-- dest  0: tmp_len  2: tree  0
-- dest  3: tmp_len  0: tree  1

-- 3 --
-- dest  2: tmp_len  2: tree  0
-- dest  4: tmp_len  0: tree  1

-- 4 --
-- dest  3: tmp_len  2: tree  0
-- dest  1: tmp_len  0: tree  1

-- 5 --
-- dest  0: tmp_len  2: tree  0
-- dest  6: tmp_len  0: tree  1

-- 6 --
-- dest  5: tmp_len  2: tree  0
-- dest  7: tmp_len  0: tree  1

-- 7 --
-- dest  6: tmp_len  2: tree  0
-- dest  1: tmp_len  0: tree  0

-- 8 --
-- dest  0: tmp_len  2: tree  0
-- dest  9: tmp_len  0: tree  1

-- 9 --
-- dest  8: tmp_len  2: tree  0
-- dest 10: tmp_len  0: tree  1

-- 10 --
-- dest  9: tmp_len  2: tree  0
-- dest 11: tmp_len  0: tree  1

-- 11 --
-- dest 10: tmp_len  2: tree  0
-- dest 12: tmp_len  0: tree  0

-- 12 --
-- dest 11: tmp_len  2: tree  0
-- dest  1: tmp_len  2: tree  0

nb start_room connection(s) : 3
nb not tube room(s) : 2
nb room(s) connected : 13 / 13
tab created
previous copied
new path allocated
len_path 6
path found
5
---- 0
---- 2
---- 3
---- 4
---- 1
-- is_passed 0 : -1 --
-- 0: 0: 8: 1
-- 0: 0: 5: 1
-- 0: 2000000: 2: 1

-- is_passed 1 : -1 --
-- 1: 0: 12: 1
-- 1: 2: 7: 0
-- 1: 0: 4: 0

-- is_passed 2 : 0 --
-- 2: 0: 0: 0
-- 2: 2000000: 3: 1

-- is_passed 3 : 0 --
-- 3: 0: 2: 0
-- 3: 2000000: 4: 1

-- is_passed 4 : 0 --
-- 4: 0: 3: 0
-- 4: 2000000: 1: 1

-- is_passed 5 : -1 --
-- 5: 2: 0: 0
-- 5: 0: 6: 1

-- is_passed 6 : -1 --
-- 6: 2: 5: 0
-- 6: 0: 7: 1

-- is_passed 7 : -1 --
-- 7: 2: 6: 0
-- 7: 0: 1: 0

-- is_passed 8 : -1 --
-- 8: 2: 0: 0
-- 8: 0: 9: 1

-- is_passed 9 : -1 --
-- 9: 2: 8: 0
-- 9: 0: 10: 1

-- is_passed 10 : -1 --
-- 10: 2: 9: 0
-- 10: 0: 11: 1

-- is_passed 11 : -1 --
-- 11: 2: 10: 0
-- 11: 0: 12: 0

-- is_passed 12 : -1 --
-- 12: 2: 11: 0
-- 12: 2: 1: 0

tab created
previous copied
new path allocated
len_path 6
path found

---- 0
---- 2
---- 3
---- 4
---- 1

---- 0
---- 5
---- 6
---- 7
---- 1
ici 0.000223
0 30 5
5 30 5
move : 34

L1-2 L31-5
L1-3 L2-2 L31-6 L32-5
L1-4 L2-3 L3-2 L31-7 L32-6 L33-5
L1-1 L2-4 L3-3 L4-2 L31-1 L32-7 L33-6 L34-5
L2-1 L3-4 L4-3 L5-2 L32-1 L33-7 L34-6 L35-5
L3-1 L4-4 L5-3 L6-2 L33-1 L34-7 L35-6 L36-5
L4-1 L5-4 L6-3 L7-2 L34-1 L35-7 L36-6 L37-5
L5-1 L6-4 L7-3 L8-2 L35-1 L36-7 L37-6 L38-5
L6-1 L7-4 L8-3 L9-2 L36-1 L37-7 L38-6 L39-5
L7-1 L8-4 L9-3 L10-2 L37-1 L38-7 L39-6 L40-5
L8-1 L9-4 L10-3 L11-2 L38-1 L39-7 L40-6 L41-5
L9-1 L10-4 L11-3 L12-2 L39-1 L40-7 L41-6 L42-5
L10-1 L11-4 L12-3 L13-2 L40-1 L41-7 L42-6 L43-5
L11-1 L12-4 L13-3 L14-2 L41-1 L42-7 L43-6 L44-5
L12-1 L13-4 L14-3 L15-2 L42-1 L43-7 L44-6 L45-5
L13-1 L14-4 L15-3 L16-2 L43-1 L44-7 L45-6 L46-5
L14-1 L15-4 L16-3 L17-2 L44-1 L45-7 L46-6 L47-5
L15-1 L16-4 L17-3 L18-2 L45-1 L46-7 L47-6 L48-5
L16-1 L17-4 L18-3 L19-2 L46-1 L47-7 L48-6 L49-5
L17-1 L18-4 L19-3 L20-2 L47-1 L48-7 L49-6 L50-5
L18-1 L19-4 L20-3 L21-2 L48-1 L49-7 L50-6 L51-5
L19-1 L20-4 L21-3 L22-2 L49-1 L50-7 L51-6 L52-5
L20-1 L21-4 L22-3 L23-2 L50-1 L51-7 L52-6 L53-5
L21-1 L22-4 L23-3 L24-2 L51-1 L52-7 L53-6 L54-5
L22-1 L23-4 L24-3 L25-2 L52-1 L53-7 L54-6 L55-5
L23-1 L24-4 L25-3 L26-2 L53-1 L54-7 L55-6 L56-5
L24-1 L25-4 L26-3 L27-2 L54-1 L55-7 L56-6 L57-5
L25-1 L26-4 L27-3 L28-2 L55-1 L56-7 L57-6 L58-5
L26-1 L27-4 L28-3 L29-2 L56-1 L57-7 L58-6 L59-5
L27-1 L28-4 L29-3 L30-2 L57-1 L58-7 L59-6 L60-5
L28-1 L29-4 L30-3 L58-1 L59-7 L60-6
L29-1 L30-4 L59-1 L60-7
L30-1 L60-1
