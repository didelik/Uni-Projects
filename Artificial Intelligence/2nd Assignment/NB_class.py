from model import *

class NaiveBayes(Model):
    def __init__(self, unique_classes):
        self.classes = unique_classes

    def train(self, dataset, labels):
        self.getData(dataset, labels)

        prob_classes=np.empty(self.classes.shape[0])
        all_words=[]
        cat_word_counts=np.empty(self.classes.shape[0])

        for cat_index,cat in enumerate(self.classes):
            prob_classes[cat_index]=np.sum(self.labels==cat)/float(self.labels.shape[0])

            count=list(self.bow_dicts[cat_index].values())
            cat_word_counts[cat_index]=np.sum(np.array(list(self.bow_dicts[cat_index].values())))+1

            all_words+=self.bow_dicts[cat_index].keys()

        self.vocab=np.unique(np.array(all_words))
        self.vocab_length=self.vocab.shape[0]

        denoms=np.array([cat_word_counts[cat_index]+self.vocab_length+1 for cat_index,cat in enumerate(self.classes)])

        self.cats_info=[(self.bow_dicts[cat_index],prob_classes[cat_index],denoms[cat_index]) for cat_index,cat in enumerate(self.classes)]
        self.cats_info=np.array(self.cats_info)

    def getExampleProb(self,test_example):
        likelihood_prob=np.zeros(self.classes.shape[0])

        for cat_index,cat in enumerate(self.classes):

            for test_token in test_example.split():
                test_token_counts=self.cats_info[cat_index][0].get(test_token,0)+1

                test_token_prob=test_token_counts/float(self.cats_info[cat_index][2])

                likelihood_prob[cat_index]+=np.log(test_token_prob)

        post_prob=np.empty(self.classes.shape[0])
        for cat_index,cat in enumerate(self.classes):
            post_prob[cat_index]=likelihood_prob[cat_index]+np.log(self.cats_info[cat_index][1])

        return post_prob

    def test(self, test_set, test_labels=0):
        predictions=[]
        for example in test_set:

            cleaned_example=preprocess_string(example)

            post_prob=self.getExampleProb(cleaned_example)

            predictions.append(self.classes[np.argmax(post_prob)])

        return np.array(predictions)
