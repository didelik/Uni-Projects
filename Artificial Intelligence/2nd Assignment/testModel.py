from NB_class import *
from ID3_class import *

def test_model(nb, id3, n):
    test_data = np.array(read_from_file(n, False))
    test_labels = np.array(([0]*n) + ([1]*n))

    print ("---------------- Testing In Progress --------------------")
    print ("Number of positive and negative test examples: " + str(len(test_labels)))

    nb_pclasses = nb.test(test_data, test_labels)
    id3_pclasses = id3.test(test_data, test_labels)

    print ('----------------- Testing Completed ---------------------\n')

    return [calculate_stats(nb_pclasses, test_labels), calculate_stats(id3_pclasses, test_labels)]
