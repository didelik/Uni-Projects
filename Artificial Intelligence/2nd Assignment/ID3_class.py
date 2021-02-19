from __future__ import print_function
from model import *

training_data = []
header = []

def class_counts(rows):
    counts = {}
    for row in rows:
        label = row[-1]  # label is always the last column
        if label not in counts:
            counts[label] = 0
        counts[label] += 1
    return counts

#print(class_counts(training_data))

class Question:

    def __init__(self, column, value):
        self.column = column
        self.value = value # asked value

    def match(self,example):
        val = example[self.column]
        return val == self.value
    """
    def __repr__(self):

        return "Contains " + header[self.column] + "?"
    """

#print(Question(2,1))


def partition(rows, question):

    true_rows, false_rows = [], []
    for row in rows:
        if question.match(row):
            true_rows.append(row)
        else:
            false_rows.append(row)
    return true_rows, false_rows

#true_rows,false_rows = partition(training_data,Question(0,1))

def gini(rows):

    counts = class_counts(rows)
    impurity = 1
    for lbl in counts:
        prob_of_lbl = counts[lbl] / float(len(rows))
        impurity -= prob_of_lbl**2
    return impurity

#print(gini(header))

def info_gain(left, right, current_uncertainty): #curr_node_imp - weighted_avg(children nodes)

    p = float(len(left)) / (len(left) + len(right))
    return current_uncertainty - p * gini(left) - (1 - p) * gini(right)

def find_best_split(rows):

    best_gain = 0
    best_question = None
    current_uncertainty = gini(rows)
    n_features = len(rows[0]) - 1 #num of columns

    for col in range(n_features): #for each voc word
        values = {0,1}
        for val in values: # for each value of this voc word
            question = Question(col,val)

            true_rows,false_rows = partition(rows, question)

            if len(true_rows) == 0 or len(false_rows) == 0:
                continue

            gain = info_gain(true_rows, false_rows, current_uncertainty)

            if gain >= best_gain:
                best_gain, best_question = gain, question

    return best_gain, best_question

#best_gain, best_question = find_best_split(training_data)


class Leaf:

    def __init__(self, rows):
        self.predictions = class_counts(rows)



class Decision_Node:

    def __init__(self,question,true_branch,false_brach):
        self.question = question
        self.true_branch = true_branch
        self.false_branch = false_brach


def build_tree(rows):

    gain, question = find_best_split(rows)

    if gain <= 0.05:
        return Leaf(rows)

    true_rows, false_rows = partition(rows,question)

    true_branch = build_tree(true_rows)
    false_branch = build_tree(false_rows)

    return Decision_Node(question,true_branch,false_branch)


def print_leaf(counts):
    total = sum(counts.values()) * 1.0
    probs = {}
    for lbl in counts.keys():
        probs[lbl] = str(int(counts[lbl] / total * 100)) + "%"
    return probs


def classify(row, node):

    if isinstance(node, Leaf):
        return node.predictions

    if node.question.match(row):
        return classify(row, node.true_branch)
    else:
        return classify(row, node.false_branch)


class ID3(Model):
    def __init__(self, unique_classes):
        self.classes = unique_classes

    def train(self, dataset, labels):
        header, training_data = self.getID3_Data(dataset, labels)
        self.tree = build_tree(training_data)

    def test(self, test_set, test_labels):
        test_data = self.getID3_Data(test_set, test_labels)[1]
        self.test_dict = [print_leaf(classify(test_data[i], self.tree)) for i in range(len(test_data))]

        return [max(item, key=item.get) for item in self.test_dict]
