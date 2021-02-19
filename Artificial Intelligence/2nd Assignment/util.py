import pandas as pd
import numpy as np
from collections import defaultdict
from collections import Counter
import re
import os
import matplotlib.pyplot as plt

def preprocess_string(str):
    cleaned_str=re.sub('[^a-z\s]+',' ',str,flags=re.IGNORECASE)
    cleaned_str=re.sub('(\s+)',' ',cleaned_str)
    cleaned_str=cleaned_str.lower()

    return cleaned_str

def calculate_stats(actual, predicted):
    true_positives = len([a for a, p in zip(actual, predicted) if a == p and p == 1])
    true_negatives = len([a for a, p in zip(actual, predicted) if a == p and p == 0])
    false_positives = len([a for a, p in zip(actual, predicted) if a != p and p == 1])
    false_negatives = len([a for a, p in zip(actual, predicted) if a != p and p == 0])

    acc = (true_positives+true_negatives) / (true_positives+true_negatives+false_positives+false_negatives)

    if((true_positives+false_positives)==0):
        prec=0
    else:
        prec = true_positives / (true_positives+false_positives)

    if((true_positives+false_negatives)==0):
        rec=0
    else:
        rec = true_positives / (true_positives+false_negatives)

    if((prec + rec)==0):
        f1=0
    else:
        f1 = 2*(prec*rec)/(prec + rec)

    return [acc, prec, rec, f1]


def get_desired_part(str, n, m):
    str_list = str.split()
    partM = list(dict(Counter(str_list).most_common(m)))
    partN = list(dict(Counter(str_list).most_common(n)))
    m_without_n = [x for x in partM if x not in partN]
    part = [x for x in str_list if x in m_without_n]

    return " ".join(part)


def read_from_file(num, ver, n=0, m=0):
    data = []

    if(ver):
        paths = ["aclImdb/train/pos", "aclImdb/train/neg"]
    else:
        paths = ["aclImdb/test/pos", "aclImdb/test/neg"]

    for path in paths:
        i=0

        for file in os.listdir(path):
            i+=1
            if(i>num):
                break

            txt = open(path + "/" + file, "r", encoding="utf8").read()
            if(ver and (n!=0 and m!=0)):
                txt = get_desired_part(txt, n, m)
            data.append(txt)

    return data
