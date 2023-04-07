import os
import time
from tqdm import tqdm

for i in tqdm(range(50)):
    os.system(f'./test_gen > {i:02d}.txt')
    time.sleep(1)
    os.system(f'zip levels.zip {i:02d}.txt')
    os.system(f'rm {i:02d}.txt')