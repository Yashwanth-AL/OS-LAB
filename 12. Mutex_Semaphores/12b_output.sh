gcc readers_writers.c -o readers_writers -pthread

./readers_writers

Reader 1: read cnt as 1
Reader 2: read cnt as 1
Reader 3: read cnt as 1
Writer 1 modified cnt to 2
Reader 1: read cnt as 2
Reader 2: read cnt as 2
Reader 3: read cnt as 2
Writer 2 modified cnt to 4
Reader 1: read cnt as 4
Reader 2: read cnt as 4
Reader 3: read cnt as 4
Writer 3 modified cnt to 8
Reader 1: read cnt as 8
Reader 2: read cnt as 8
Reader 3: read cnt as 8
