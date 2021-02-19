from util import *

class Model:

    def addToBow(self, example, dict_index):
        if isinstance(example,np.ndarray): example=example[0]

        for token_word in example.split():
            self.bow_dicts[dict_index][token_word]+=1

    def getData(self, dataset, labels):
        self.examples=dataset
        self.labels=labels
        self.bow_dicts=np.array([defaultdict(lambda:0) for index in range(self.classes.shape[0])]) #bags of words

        if not isinstance(self.examples,np.ndarray): self.examples=np.array(self.examples)
        if not isinstance(self.labels,np.ndarray): self.labels=np.array(self.labels)

        for cat_index,cat in enumerate(self.classes):
            all_cat_examples=self.examples[self.labels==cat]

            cleaned_examples=[preprocess_string(cat_example) for cat_example in all_cat_examples]
            cleaned_examples=pd.DataFrame(data=cleaned_examples)

            np.apply_along_axis(self.addToBow,1,cleaned_examples,cat_index)

    def getID3_Data(self, dataset, labels):
        data=[]
        self.getData(dataset, labels)

        header = [list(self.bow_dicts[i].keys()) for i in range(len(self.bow_dicts))]
        header = list(set(header[0]+header[1]))

        for example in dataset:
            data.append([0]*len(header))

            cleaned_example = preprocess_string(example)
            for token in cleaned_example.split():
                data[-1][header.index(token)]=1

        header.append("label")
        for test_indx, test_item in enumerate(data):
            test_item.append(labels[test_indx])


        return [header, data]




    # def getID3_Labels(self, labels):
