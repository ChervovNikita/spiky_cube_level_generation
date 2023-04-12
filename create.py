import os
import time
from tqdm import tqdm

rules = {
    0: 327687,
    1: 131078
}


def read_ints(row):
    return [int(val) for val in row.split()]


def gen_tile_data(mat):
    next_row = 65536
    current = []
    for i in range(len(mat)):
        for j in range(len(mat[0])):
            current.append(next_row * i + j)
            current.append(0)
            state = 0
            val = mat[i][j]
            if val != 5:
                state = 0
            if val == 5:
                state = 1
            current.append(rules[state])
    return ', '.join([str(val) for val in current])


def gen_tscn(chapter, level, mat):
    tile_data = gen_tile_data(mat)
    code = open('base_structure', 'r').read()
    code = code.replace('{chapter}', str(chapter)).replace('{level}', str(level)).replace('{tile_data}', tile_data)
    return code


def gen_cs(chapter, level):
    code = open('base_cs', 'r').read()
    code = code.replace('{chapter}', str(chapter)).replace('{level}', str(level))
    return code


for chapter in range(1, 3 + 1):
    os.system(f'mkdir levels/Chapter{chapter}')
    for level in tqdm(range(1, 20 + 1)):
        if chapter == 1 and level <= 3: continue  # first levels were made manually
        os.system(f'mkdir levels/Chapter{chapter}/Level{level}')
        os.system(f'./test_gen > tmp.txt')
        lines = open(f'tmp.txt', 'r').readlines()

        os.system(f'cp tmp.txt mat_{chapter}_{level}.txt')
        os.system(f'zip levels.zip mat_{chapter}_{level}.txt')
        os.system(f'rm mat_{chapter}_{level}.txt')
        os.system(f'rm tmp.txt')

        n, m = read_ints(lines[0])
        a = []
        for i in range(1, len(lines)):
            a.append(read_ints(lines[i]))
            # print(a[-1])

        code = gen_tscn(chapter, level, a)

        with open(f'levels/Chapter{chapter}/Level{level}/Level_{chapter}_{level}.cs', 'w') as f:
            f.write(gen_cs(chapter, level))

        with open(f'levels/Chapter{chapter}/Level{level}/Level_{chapter}_{level}.tscn', 'w') as f:
            f.write(code)

        time.sleep(1)