from NB_class import *
from ID3_class import *

def train_model(num, n, m):
    train_data = np.array(read_from_file(num, True, n, m))
    train_labels = np.array(([0]*num) + ([1]*num))

    nb = NaiveBayes(np.unique(train_labels))
    id3 = ID3(np.unique(train_labels))

    print ("---------------- Training In Progress --------------------")
    print ("Number of positive and negative train examples: " + str(len(train_labels)))

    nb.train(train_data,train_labels)
    id3.train(train_data,train_labels)

    nb_pclasses = nb.test(train_data)
    nb_train_acc = calculate_stats(nb_pclasses, train_labels)[0]

    id3_pclasses = id3.test(train_data, train_labels)
    id3_train_acc = calculate_stats(id3_pclasses, train_labels)[0]

    print ('----------------- Training Completed ---------------------\n')

    return [nb, id3, nb_train_acc, id3_train_acc]
    # return [id3, train_acc]
