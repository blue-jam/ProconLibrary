struct PMA{
    int id;
    PMA *next[0x100];       //next[0] is for fail
    vector<int> accept;
    PMA() { fill(next, next + 0x100, (PMA*)NULL); }
};
//Pattern Matching AutoMaton
void buildPMA(vector<string> &words, vector<PMA*> &vp){
    int n = words.size();
    PMA *root = new PMA;    //createTrie
    root -> id = 0;
    vp.push_back(root);
    int count = 1;
    for(int i = 0; i<n; ++i){
        PMA *v = root;
        int m = words[i].size();
        for(int j = 0; j < m; ++j){
            int c = words[i][j];
            if(v -> next[c] == NULL){
                v -> next[c] = new PMA;
                v -> next[c] -> id = count++;
                vp.push_back(v -> next[c]);
            }
            v = v -> next[c];
        }
        v -> accept.push_back(i);
    }
    queue<PMA*> Q;          //make failure link
    for(int c = 1; c < 0x100; ++c){
        if(root -> next[c] != NULL){
            root -> next[c] -> next[0] = root;
            Q.push(root -> next[c]);
        } else root -> next[c] = root;
    }
    while(!Q.empty()){
        PMA *v = Q.front(); Q.pop();
        for(int c = 1; c < 0x100; ++c){
            if(v -> next[c] != NULL) 
                Q.push(v -> next[c]);
            PMA *r = v -> next[0];
            while(r -> next[c] == NULL) r = r -> next[0];
            if(v -> next[c] != NULL)
                v -> next[c] -> next[0] = r -> next[c];
            else
                v -> next[c] = r -> next[c];
        }
        v -> accept.insert(v -> accept.end(), ALL(v -> next[0] -> accept));
    }
}
