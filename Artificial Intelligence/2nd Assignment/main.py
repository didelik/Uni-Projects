from trainModel import*
from testModel import *

reps=range(3)
test_data_num = 500

NB_train_accuracy = []
NB_test_accuracy = []
NB_test_precision = []
NB_test_recall = []
NB_test_f1 = []

ID3_train_accuracy = []
ID3_test_accuracy = []
ID3_test_precision = []
ID3_test_recall = []
ID3_test_f1 = []

def graph():
    plt.figure()
    plt.style.use('ggplot')

    ax1 = plt.subplot(2, 2, 1) # Top left plot
    ax1.title.set_text('Accuracy')
    ax1.plot(reps, NB_test_accuracy, color='blue', alpha=0.3)
    ax1.scatter(reps, NB_test_accuracy, color='blue', alpha=0.3)

    ax1.plot(reps, ID3_test_accuracy, color='red', alpha=0.3)
    ax1.scatter(reps, ID3_test_accuracy, color='red', alpha=0.3)

    ax1.plot(reps, NB_train_accuracy, color='blue', alpha=0.1)
    ax1.scatter(reps, NB_train_accuracy, color='blue', alpha=0.1)

    ax1.plot(reps, ID3_train_accuracy, color='red', alpha=0.1)
    ax1.scatter(reps, ID3_train_accuracy, color='red', alpha=0.1)

    ax1.legend(["Naive Bayes", "ID3"], loc ="lower right")
    ax1.grid(True)

    ax2 = plt.subplot(2, 2, 2) # Top right plot
    ax2.title.set_text('Precision')
    ax2.plot(reps, NB_test_precision, color='blue', alpha=0.3)
    ax2.scatter(reps, NB_test_precision, color='blue', alpha=0.3)

    ax2.plot(reps, ID3_test_precision, color='red', alpha=0.3)
    ax2.scatter(reps, ID3_test_precision, color='red', alpha=0.3)

    ax2.legend(["Naive Bayes", "ID3"], loc ="lower right")
    ax2.grid(True)

    ax3 = plt.subplot(2, 2, 3) # Bottom left plot
    ax3.title.set_text('Recall')
    ax3.plot(reps, NB_test_recall, color='blue', alpha=0.3)
    ax3.scatter(reps, NB_test_recall, color='blue', alpha=0.3)

    ax3.plot(reps, ID3_test_recall, color='red', alpha=0.3)
    ax3.scatter(reps, ID3_test_recall, color='red', alpha=0.3)

    ax3.legend(["Naive Bayes", "ID3"], loc ="lower right")
    ax3.grid(True)

    ax4 = plt.subplot(2, 2, 4) # Bottom right plot
    ax4.title.set_text('F1')
    ax4.plot(reps, NB_test_f1, color='blue', alpha=0.3)
    ax4.scatter(reps, NB_test_f1, color='blue', alpha=0.3)

    ax4.plot(reps, ID3_test_f1, color='red', alpha=0.3)
    ax4.scatter(reps, ID3_test_f1, color='red', alpha=0.3)

    ax4.legend(["Naive Bayes", "ID3"], loc ="lower right")
    ax4.grid(True)

    plt.subplots_adjust(top=0.92, bottom=0.08, left=0.10, right=0.95, hspace=0.25, wspace=0.35)
    plt.show()

def repetition(i, n, m):
    counter = int((12500/10)*(i+1)) # Gets a percentage of our train data

    trained_models = train_model(counter, n, m) # Trains both models
    test_results = test_model(trained_models[0], trained_models[1], test_data_num) # Tests both models

    return [[trained_models[2], test_results[0][0], test_results[0][1], test_results[0][2], test_results[0][3]], [trained_models[3], test_results[1][0], test_results[1][1], test_results[1][2], test_results[1][3]]]

def main(n=0, m=0):
    for i in reps:
        print("Repetition: " + str(i+1))

        result = repetition(i, n, m)

        NB_train_accuracy.append(result[0][0])
        NB_test_accuracy.append(result[0][1])
        NB_test_precision.append(result[0][2])
        NB_test_recall.append(result[0][3])
        NB_test_f1.append(result[0][4])

        ID3_train_accuracy.append(result[1][0])
        ID3_test_accuracy.append(result[1][1])
        ID3_test_precision.append(result[1][2])
        ID3_test_recall.append(result[1][3])
        ID3_test_f1.append(result[1][4])

    print("\nNaive Bayes train data Accuracy:")
    print(NB_train_accuracy)
    print("Naive Bayes test data Accuracy:")
    print(ID3_test_accuracy)
    print("Naive Bayes test data Precision:")
    print(NB_test_precision)
    print("Naive Bayes test data Recall:")
    print(NB_test_recall)
    print("Naive Bayes test data F1:")
    print(NB_test_f1)

    print("\nID3 train data Accuracy:")
    print(ID3_train_accuracy)
    print("ID3 test data Accuracy:")
    print(ID3_test_accuracy)
    print("ID3 test data Precision:")
    print(ID3_test_precision)
    print("ID3 test data Recall:")
    print(ID3_test_recall)
    print("ID3 test data F1:")
    print(ID3_test_f1)

    graph()

main(25, 40)
