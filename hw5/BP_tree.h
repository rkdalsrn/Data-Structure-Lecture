#include <string>
#include <string.h>
#include <cstring>
#include <fstream>
#include <queue>
#include "BP_node.h"

using namespace std;

class BPTree{
public:
    // member variables
    BPNode* root;
    
    // constructor & destructor
    BPTree();
    ~BPTree();
    
    //member functions
    void insert_data(int i_data);
    void insert_data(string s_data);
    void bulk_loading(ifstream* ifs);
    void traverse();
    
    BPNode* split_node(BPNode* node, bool insert_type, int i_data);
    BPNode* split_node(BPNode* node, bool insert_type, string s_data);
    void h_print(BPNode* BPN);
    BPNode* get_root();
};

BPTree::BPTree(){
    root = new BPNode();
}

BPTree::~BPTree(){
    // TODO
    delete root;
}

void BPTree::insert_data(int i_data){
    BPNode* BPN = root;
    
    // traverse to proper leaf node
    while(BPN->is_leaf() == NONLEAF){
        bool determined = 0;
        for(int i = 0; i < BPN->numInteger; ++i){
            if(i_data < *(int*)(BPN->data[i])){
                BPN = BPN->childPtr[i];
                determined = 1;
                break;
            }
        }
        if(determined == 0){
            BPN = BPN->childPtr[BPN->numInteger];
            determined = 1;
        }
    }
    
    // initial insert
    if(BPN == root && BPN->is_empty() == EMPTY){
        BPN->data[0] = new int(i_data);
        (BPN->num)++;
        (BPN->numInteger)++;
        return;
    }
    
    // not an initial insert
    if(BPN->is_full() == UNFULL){
        // insert data with comparison
        // compare int in range (0, numInteger-1)
        bool inserted = 0;
        /*
         TODO
         */
        int temp = i_data;
        for (int j = BPN->num; j > BPN->numInteger; --j) {
            BPN->data[j] = BPN->data[j - 1];
        }
        for(int i = 0; i < BPN->numInteger; i++){
            if(*(int*)BPN->data[i] > temp){
                int tmp = temp;
                temp = *(int*)(BPN->data[i]);
                delete (int*)BPN->data[i];
                BPN->data[i] = new int(tmp);
            }
        }
        BPN->data[BPN->numInteger] = new int(temp);
        inserted = 1;
        (BPN->num)++;
        (BPN->numInteger)++;
        
    }
    else{
        // if the node is full
        split_node(BPN, SINGLY, i_data);
    }
}

void BPTree::insert_data(string s_data){
    BPNode* BPN = root;
    
    // traverse to proper leaf node
    while(BPN->is_leaf() == NONLEAF){
        bool determined = 0;
        for(int i = BPN->numInteger; i < BPN->num; ++i){
            if(strcmp(s_data.c_str(), (*(string*)(BPN->data[i])).c_str()) < 0){
                BPN = BPN->childPtr[i];
                determined = 1;
                break;
            }
        }
        if(determined == 0){
            BPN = BPN->childPtr[BPN->num];
            determined = 1;
        }
    }
    
    // initial insert
    if(BPN == root && BPN->is_empty() == EMPTY){
        BPN->data[0] = new string(s_data);
        (BPN->num)++;
        return;
    }
    
    // not an initial insert
    if(BPN->is_full() == UNFULL){
        // insert data with comparison
        // compare string in range (numInteger, num)
        bool inserted = 0;
        /*
         TODO
         */
        int ming = BPN->numInteger;
        for(int i = BPN->numInteger; i < BPN->num; i++){
            if(strcmp(s_data.c_str(), (*(string*)(BPN->data[i])).c_str()) > 0){
                ming = ming + 1;
            }
        }
        for(int i = BPN->num; i > ming; --i){
            BPN->data[i] = BPN->data[i-1];
        }
        (BPN->num)++;
        BPN->data[ming] = new string(s_data);
        inserted = 1;
    }
    else{
        // if the node is full
        split_node(BPN, SINGLY, s_data);
    }
}

void BPTree::bulk_loading(ifstream* ifs){
    BPNode* BPN = root;
    int numInt = 0;
    int numTotal = 0;
    int rowCount = 0;
    string sBuf;
    
    // traverse to proper leaf node
    while(BPN->is_leaf() == NONLEAF){
        BPN = BPN->childPtr[BPN->num];
    }
    
    while(getline(*ifs, sBuf)){
        if(rowCount == 0){
            numInt = stoi(sBuf);
            rowCount++;
        }
        else if(rowCount == 1){
            numTotal = stoi(sBuf);
            rowCount++;
        }
        else{
            if(numInt > 0){
                // insert int data
                numInt--;
                if(BPN->is_full() == UNFULL){
                    BPN->data[BPN->num] = new int(stoi(sBuf));
                    (BPN->num)++;
                    (BPN->numInteger)++;
                }
                else{
                    split_node(BPN, BULK, stoi(sBuf));
                    
                    // traver again to proper leaf node
                    BPN = root;
                    while(BPN->is_leaf() == NONLEAF){
                        BPN = BPN->childPtr[BPN->num];
                    }
                }
            }
            else{
                // insert string data
                if(BPN->is_full() == UNFULL){
                    BPN->data[BPN->num] = new string(sBuf);
                    (BPN->num)++;
                }
                else{
                    split_node(BPN, BULK, sBuf);
                    
                    // traver again to proper leaf node
                    BPN = root;
                    while(BPN->is_leaf() == NONLEAF){
                        BPN = BPN->childPtr[BPN->num];
                    }
                }
            }
        }
    }
    
}

BPNode* BPTree::split_node(BPNode* node, bool insert_type, int i_data){
    // CASE : inserted data is "INTEGER TYPE"
    
    BPNode* sNode = new BPNode();       // generated node while splitting
    BPNode* pNode = node->parentPtr;    // parent node of the node will be splitted
    int i_med;          // integer type median
    string s_med;       // string type median
    bool medType = 0;   // 1 for int, o for string
    
    // generated node and splitted node are same leaf or not
    sNode->set_leaf(node->is_leaf());
    
    // split_node called by singly insert_node
    // split node 3/3
    if(insert_type == SINGLY){
        if(node->numInteger < 3){
            // median will be string
            // s_data must be in node
            medType = SMED;
            
            // move data[2-4] of node to data[0-2] of sNode
            // remove data[2-4] of node by decrease num of node
            // set s_med with data[0] of sNode
            /*
             TODO
             */
            for(int i = 4; i > 1; --i){
                sNode->data[i-2] = node->data[i];
                (node->num)--;
                if(i < node->numInteger){
                    (sNode->numInteger)++;
                    (node->numInteger)--;
                }
                (sNode->num)++;
            }
            s_med = *(string*)sNode->data[0];
            
            // if splitted node is "not a leaf node"
            if(node->is_leaf() == NONLEAF){
                // delete median from sNode
                // copy child pointer from node to sNode
                
                //delete data[0] of sNode
                
                delete (string*)sNode->data[0];
                for(int i = 0; i < sNode->num-1; ++i){
                    sNode->data[i] = sNode->data[i+1];
                    sNode->childPtr[i] = node->childPtr[i+4];
                    node->childPtr[i+4] = NULL;
                    sNode->childPtr[i]->parentPtr = sNode;
                }
                (sNode->num)--;
            }
            
            // insert i_data to node
            /*
             TODO
             */
            int temp = i_data;
            for(int i = 0; i < node->numInteger; i++){
                if(*(int*)node->data[i] > temp){
                    int tmp = temp;
                    temp = *(int*)(node->data[i]);
                    delete (int*)node->data[i];
                    node->data[i] = new int(tmp);
                }
            }
            for(int j = node->num; j > node->numInteger; --j){
                node->data[j] = node->data[j-1];
            }
            node->data[node->numInteger] = new int(temp);
            (node->num)++;
            (node->numInteger)++;
            
        }
        else{
            // median will be integer
            medType = IMED;
            
            // find the position of i_data
            int newPos = 0;
            bool determined = 0;
            for(int i = 0; i < node->numInteger; ++i){
                if(i_data < *(int*)(node->data[i])){
                    newPos = i;
                    determined = 1;
                    break;
                }
            }
            if(determined == 0){
                newPos = node->numInteger;
                determined = 1;
            }
            
            // case 1 : i_data remains on node
            if(newPos < 3){
                // move data[2-4] of node to data[0-2] of sNode
                // remove data[2-4] of node by decrease num of node
                // set i_med
                /*
                 TODO
                 */
                for(int i = 4; i > 1; --i){
                    sNode->data[i-2] = node->data[i];
                    (node->num)--;
                    if(i < node->numInteger){
                        (sNode->numInteger)++;
                        (node->numInteger)--;
                    }
                    (sNode->num)++;
                }
                i_med = *(int*)sNode->data[0];
                
                //insert i_data to node
                /*
                 TODO
                 */
                int temp = i_data;
                for(int i = 0; i < node->numInteger; i++){
                    if(*(int*)node->data[i] > temp){
                        int tmp = temp;
                        temp = *(int*)(node->data[i]);
                        delete (int*)node->data[i];
                        node->data[i] = new int(tmp);
                    }
                }
                node->data[node->numInteger] = new int(temp);
                (node->num)++;
                (node->numInteger)++;
                
            }
            // case 2 : i_data moves to sNode
            else{
                // move data[3-4] of node to data[0-1] of sNode
                // remove data[3-4] of node by decrease num of node
                /*
                 TODO
                 */
                for(int i = 4; i > 2; --i){
                    sNode->data[i-3] = node->data[i];
                    (node->num)--;
                    if(i < node->numInteger){
                        (sNode->numInteger)++;
                        (node->numInteger)--;
                    }
                    (sNode->num)++;
                }
                
                //insert i_data to sNode
                //set i_med
                /*
                 TODO
                 */
                int temp = i_data;
                for(int i = 0; i < sNode->numInteger; i++){
                    if(*(int*)sNode->data[i] > temp){
                        int tmp = temp;
                        temp = *(int*)(sNode->data[i]);
                        delete (int*)sNode->data[i];
                        sNode->data[i] = new int(tmp);
                    }
                }
                if(((sNode->num)-(sNode->numInteger)) != 0){
                    for(int i = sNode->num; i > sNode->numInteger; i--){
                        sNode->data[i] = sNode->data[i-1];
                    }
                }
                sNode->data[sNode->numInteger] = new int(temp);
                (sNode->num)++;
                (sNode->numInteger)++;
                i_med = *(int*)sNode->data[0];
                
            }
            
            // if splitted node is "not a leaf node"
            if(node->is_leaf() == NONLEAF){
                // delete median from sNode
                // copy child pointer from node to sNode
                
                //delete data[0] of sNode
                
                delete (int*)sNode->data[0];
                for(int i = 0; i < sNode->num-1; ++i){
                    sNode->data[i] = sNode->data[i+1];
                    sNode->childPtr[i] = node->childPtr[i+4];
                    node->childPtr[i+4] = NULL;
                    sNode->childPtr[i]->parentPtr = sNode;
                }
                (sNode->num)--;
                (sNode->numInteger)--;
            }
        }
        
        // add median and pointer to sNode to parent node
        if(pNode == NULL){
            // if splitted node is the root
            // make a empty node and link it to parent pointer of node
            root = new BPNode();
            if(medType == IMED){
                root->data[0] = new int(i_med);
                (root->numInteger)++;
            }
            else{
                root->data[0] = new string(s_med);
            }
            (root->num)++;
            root->childPtr[0] = node;
            root->childPtr[1] = sNode;
            node->parentPtr = root;
            sNode->parentPtr = root;
            root->set_leaf(NONLEAF);
        }
        else if(pNode->is_full() == UNFULL){
            // if parent node has room for a new data
            int medPos = 0;     // position that median will be inserted
            bool determined = 0;
            for(int i = 0; i < pNode->num; ++i){
                if(pNode->childPtr[i] == node){
                    medPos = i;
                    determined = 1;
                    break;
                }
            }
            if(determined == 0){
                medPos = pNode->num;
                determined = 1;
            }
            
            for(int i = pNode->num; i > medPos; --i){
                pNode->childPtr[i+1] = pNode->childPtr[i];
                pNode->data[i] = pNode->data[i-1];
            }
            pNode->childPtr[medPos+1] = sNode;
            sNode->parentPtr = pNode;
            if(medType == IMED){
                pNode->data[medPos] = new int(i_med);
                (pNode->numInteger)++;
            }
            else{
                pNode->data[medPos] = new string(s_med);
            }
            (pNode->num)++;
            pNode->set_leaf(NONLEAF);
        }
        else{
            // if parent node does "NOT" have room for a new data
            // recursively split the parent node
            if(medType == IMED){
                // TODO
                /*BPNode* temp = this->split_node(pNode, BULK, i_med);
                 int det = 0;
                 for(int i = 0; i < temp->numInteger; i++){
                 if(*(int*)(temp->data[i]) == i_med){
                 det = 1;
                 for(int j = 2; j > i+1; j--){
                 temp->childPtr[j] = temp->childPtr[j-1];
                 }
                 temp->childPtr[i+1] = sNode;
                 sNode->parentPtr = temp;
                 break;
                 }
                 }
                 for(int i = 0; i < pNode->numInteger; i++){
                 if(*(int*)(pNode->data[i]) == i_med){
                 det = 1;
                 BPNode* mingu = pNode->childPtr[3];
                 for(int j = 3; j >= i+2; j--){
                 pNode->childPtr[j] = pNode->childPtr[j-1];
                 }
                 pNode->childPtr[i+1] = sNode;
                 for(int k = 2; k > 0; k--){
                 temp->childPtr[k] = temp->childPtr[k-1];
                 }
                 temp->childPtr[0] = mingu;
                 sNode->parentPtr = pNode;
                 break;
                 }
                 }
                 
                 if(det == 0){
                 pNode->childPtr[3] = node;
                 for(int j = 2; j > 0; j--){
                 temp->childPtr[j] = temp->childPtr[j-1];
                 }
                 temp->childPtr[0] = sNode;
                 sNode->parentPtr = temp;
                 }
                 for(int i = 0; i <= pNode->num-1; i++){
                 pNode->childPtr[i]->parentPtr = pNode;
                 }
                 for(int j = 0; j <= temp->num-1; j++){
                 temp->childPtr[j]->parentPtr = temp;
                 }*/
                
                int ming = 0;
                for(int i = 0; i <= CAPACITY; i++){
                    if(pNode->childPtr[ming] != node)   ming++;
                    else    break;
                }
                if(ming < 3){
                    BPNode* temp = this->split_node(pNode, SINGLY, i_med);
                    sNode->parentPtr = pNode;
                    for(int i = 3; i > ming; --i){
                        pNode->childPtr[i+1] = pNode->childPtr[i];
                    }
                    pNode->childPtr[ming + 1] = sNode;
                    sNode->parentPtr = pNode;
                    temp->childPtr[2] = temp->childPtr[1];
                    temp->childPtr[1] = temp->childPtr[0];
                    temp->childPtr[0] = pNode->childPtr[4];
                    pNode->childPtr[4] = NULL;
                    
                }
                else if(ming == 3){
                    sNode->parentPtr = split_node(pNode, SINGLY, i_med);
                    for(int i = 5; i > ming; --i){
                        sNode->parentPtr->childPtr[i-3] = sNode->parentPtr->childPtr[i-4];
                    }
                    sNode->parentPtr->childPtr[ming-3] = sNode;
                    sNode->parentPtr->childPtr[ming-3]->parentPtr = sNode->parentPtr;
                    
                }
                else{
                    BPNode* temp = this->split_node(pNode, SINGLY, i_med);
                    for(int j = 2; j > ming-3; j--){
                        temp->childPtr[j] = temp->childPtr[j-1];
                    }
                    temp->childPtr[ming-3] = sNode;
                    sNode->parentPtr = temp;
                    node->parentPtr = temp;
                }

            }
            else{
                // TODO
                /*BPNode* temp = this->split_node(pNode, BULK, s_med);
                 int det = 0;
                 for(int i = temp->numInteger; i < temp->num; i++){
                 if(*(string*)(temp->data[i]) == s_med){
                 for(int j = 2; j > i+1; j--){
                 temp->childPtr[j] = temp->childPtr[j-1];
                 }
                 temp->childPtr[i+1] = sNode;
                 sNode->parentPtr = temp;
                 det = 1;
                 break;
                 }
                 }
                 
                 for(int i = pNode->numInteger; i < pNode->num; i++){
                 if(*(string*)(pNode->data[i]) == s_med){
                 BPNode* mingu = pNode->childPtr[3];
                 for(int j = 3; j > i+1; j--){
                 pNode->childPtr[j] = pNode->childPtr[j-1];
                 }
                 pNode->childPtr[i+1] = sNode;
                 for(int j = 2; j > 0; j--){
                 temp->childPtr[j] = temp->childPtr[j-1];
                 }
                 temp->childPtr[0] = mingu;
                 sNode->parentPtr = pNode;
                 det = 1;
                 break;
                 }
                 }
                 
                 if(det == 0){
                 pNode->childPtr[3] = node;
                 for(int j = 2; j > 0; j--){
                 temp->childPtr[j] = temp->childPtr[j-1];
                 }
                 temp->childPtr[0] = sNode;
                 sNode->parentPtr = temp;
                 }
                 for(int i = 0; i < pNode->num; i++){
                 pNode->childPtr[i]->parentPtr = pNode;
                 }
                 for(int j = 0; j < temp->num; j++){
                 temp->childPtr[j]->parentPtr = temp;
                 }*/
                
                int ming = 0;
                for(int i = 0; i <= CAPACITY; i++){
                    if(pNode->childPtr[ming] != node)   ming++;
                    else    break;
                }
                if(ming < 3){
                    BPNode* temp = this->split_node(pNode, SINGLY, s_med);
                    sNode->parentPtr = pNode;
                    for(int i = 3; i > ming; --i){
                        pNode->childPtr[i+1] = pNode->childPtr[i];
                    }
                    sNode->parentPtr = pNode;
                    pNode->childPtr[ming + 1] = sNode;
                    temp->childPtr[2] = temp->childPtr[1];
                    temp->childPtr[1] = temp->childPtr[0];
                    temp->childPtr[0] = pNode->childPtr[4];
                    pNode->childPtr[4] = NULL;
                }
                else if(ming == 3){
                    sNode->parentPtr = split_node(pNode, SINGLY, s_med);
                    for(int i = 5; i > ming; --i){
                        sNode->parentPtr->childPtr[i-3] = sNode->parentPtr->childPtr[i-4];
                    }
                    sNode->parentPtr->childPtr[ming-3] = sNode;
                    sNode->parentPtr->childPtr[ming-3]->parentPtr = sNode->parentPtr;
                    
                }
                else{
                    BPNode* temp = this->split_node(pNode, SINGLY, s_med);
                    for(int j = 2; j > ming-3; j--){
                        temp->childPtr[j] = temp->childPtr[j-1];
                    }
                    temp->childPtr[ming-3] = sNode;
                    sNode->parentPtr = temp;
                    node->parentPtr = temp;
                }
                
            }
        }
    }
    // split_node called by bulk_loading
    // split node 4/2
    // i_data is always inserted to sNode;
    else{
        // move data[4] of node to data[0] of sNode
        // remove data[4] of node by decrease num of node
        // set i_med
        sNode->data[0] = node->data[4];
        (node->num)--;
        (sNode->num)++;
        if(node->numInteger >= CAPACITY-1){
            // median will be integer
            medType = IMED;
            (node->numInteger)--;
            (sNode->numInteger)++;
            i_med = *(int*)(sNode->data[0]);
        }
        else{
            // median will be string
            medType = SMED;
            s_med = *(string*)(sNode->data[0]);
        }
        // insert i_data to sNode;
        // i_data is always inserted at the end
        sNode->data[sNode->num] = new int(i_data);
        (sNode->num)++;
        (sNode->numInteger)++;
        
        // if splitted node is "not a leaf node"
        if(node->is_leaf() == NONLEAF){
            
            //delete data[0] of sNode
            
            delete (int*)sNode->data[0];
            sNode->data[0] = sNode->data[1];
            (sNode->num)--;
            (sNode->numInteger)--;
            sNode->childPtr[0] = node->childPtr[5];
            node->childPtr[5] = NULL;
            sNode->childPtr[0]->parentPtr = sNode;
        }
        
        // add median and pointer to sNode to parent node
        if(pNode == NULL){
            // if splitted node is the root
            // make a empty node and link it to parent pointer of node
            root = new BPNode();
            if(medType == IMED){
                root->data[0] = new int(i_med);
                (root->numInteger)++;
            }
            else{
                root->data[0] = new string(s_med);
            }
            (root->num)++;
            root->childPtr[0] = node;
            root->childPtr[1] = sNode;
            node->parentPtr = root;
            sNode->parentPtr = root;
            root->set_leaf(NONLEAF);
        }
        else if(pNode->is_full() == UNFULL){
            // if parent node has room for a new data
            pNode->childPtr[pNode->num+1] = sNode;
            sNode->parentPtr = pNode;
            if(medType == IMED){
                pNode->data[pNode->num] = new int(i_med);
                (pNode->numInteger)++;
            }
            else{
                pNode->data[pNode->num] = new string(s_med);
            }
            (pNode->num)++;
            pNode->set_leaf(NONLEAF);
        }
        else{
            // if parent node does "NOT" have room for a new data
            if(medType == IMED){
                // TODO
                BPNode* temp = this->split_node(pNode, BULK, i_med);
                temp->childPtr[temp->num] = sNode;
                int determined = 0;
                for(int i = 0; i <= pNode->num-1; i++){
                    if(typeid(pNode->data[i]) == typeid(sNode->data[0])){
                        if(pNode->data[i] == sNode->data[0]){
                            determined = 1;
                        }
                    }
                }
                if(determined == 1)     sNode->parentPtr = pNode;
                else        sNode->parentPtr = temp;
            }
            else{
                // TODO
                BPNode* temp = this->split_node(pNode, BULK, s_med);
                temp->childPtr[temp->num] = sNode;
                int determined = 0;
                for(int i = 0; i <= pNode->num-1; i++){
                    if(typeid(pNode->data[i]) == typeid(sNode->data[0])){
                        if(pNode->data[i] == sNode->data[0]){
                            determined = 1;
                        }
                    }
                }
                if(determined == 1)     sNode->parentPtr = pNode;
                else    sNode->parentPtr = temp;
            }
        }
    }
    
    if(node->is_leaf() == LEAF){
        sNode->childPtr[CAPACITY] = node->childPtr[CAPACITY];
        node->childPtr[CAPACITY] = sNode;
    }
    return sNode;
}

BPNode* BPTree::split_node(BPNode* node, bool insert_type, string s_data){
    // CASE : inserted data is "VARCHAR(STRING) TYPE"
    
    BPNode* sNode = new BPNode();       // generated node while splitting
    BPNode* pNode = node->parentPtr;    // parent node of the node will be splitted
    int i_med;          // integer type median
    string s_med;       // string type median
    bool medType = 0;   // 1 for int, o for string
    
    // generated node and splitted node are same leaf or not
    sNode->set_leaf(node->is_leaf());
    
    // split_node called by singly insert_node
    // split node 3/3
    if(insert_type == SINGLY){
        if(node->numInteger < 4){
            // median will be string
            medType = SMED;
            
            //find the position of s_data
            int newPos = node->numInteger;
            bool determined = 0;
            for(int i = node->numInteger; i < node->num; ++i){
                if(strcmp(s_data.c_str(), (*(string*)(node->data[i])).c_str()) < 0){
                    newPos = i;
                    determined = 1;
                    break;
                }
            }
            if(determined == 0){
                newPos = node->num;
                determined = 1;
            }
            
            // case 1 : s_data reamins on node
            if(newPos < 3){
                // move data[2-4] of node to data[0-2] of sNode
                // remove data[2-4] of node by decrease num of node
                // set s_med
                /*
                 TODO
                 */
                for(int i = 4; i > 1; --i){
                    sNode->data[i-2] = node->data[i];
                    (node->num)--;
                    if(i < node->numInteger){
                        (sNode->numInteger)++;
                        (node->numInteger)--;
                    }
                    (sNode->num)++;
                }
                s_med = *(string*)sNode->data[0];
            }
            // case 2 : s_data moves to sNode
            else{
                // move data[3-4] of node to data[0-1] of sNode
                // remove data[3-4] of node by decrease num of node
                /*
                 TODO
                 */
                for(int i = 4; i > 2; --i){
                    sNode->data[i-3] = node->data[i];
                    (node->num)--;
                    if(i < node->numInteger){
                        (sNode->numInteger)++;
                        (node->numInteger)--;
                    }
                    (sNode->num)++;
                }
                
                //insert s_data to sNode
                //set s_med
                /*
                 TODO
                 */
                string temp = s_data;
                for(int i = sNode->numInteger; i < sNode->num; i++){
                    if(strcmp((*(string*)sNode->data[i]).c_str(), temp.c_str()) > 0){
                        string tmp = temp;
                        temp = *(string*)(sNode->data[i]);
                        delete (string*)sNode->data[i];
                        sNode->data[i] = new string(tmp);
                    }
                }
                sNode->data[(sNode->num)] = new string(temp);
                (sNode->num)++;
                s_med = *(string*)sNode->data[0];
            }
            
            // if splitted node is "not a leaf node"
            if(node->is_leaf() == NONLEAF){
                // delete median from sNode
                // copy child pointer from node to sNode
                
                //delete data[0] of sNode
                
                delete (string*)sNode->data[0];
                for(int i = 0; i < sNode->num-1; ++i){
                    sNode->data[i] = sNode->data[i+1];
                    sNode->childPtr[i] = node->childPtr[i+4];
                    node->childPtr[i+4] = NULL;
                    sNode->childPtr[i]->parentPtr = sNode;
                }
                (sNode->num)--;
            }
        }
        else{
            // median will be integer
            // s_data must be in sNode
            medType = IMED;
            
            // move data[3-4] of node to data[0-1] of sNode
            // remove data[3-4] of node by decrease num of node
            // set i_med
            for(int i = 0; i < 2; ++i){
                sNode->data[i] = node->data[i+3];
                (sNode->num)++;
            }
            sNode->numInteger = node->numInteger - 3;
            node->num = 3;
            node->numInteger = 3;
            i_med = *(int*)(sNode->data[0]);
            
            // if splitted node is "not a leaf node"
            if(node->is_leaf() == NONLEAF){
                // delete median from sNode
                // copy child pointer from node to sNode
                
                //delete data[0] of sNode
                
                delete (int*)sNode->data[0];
                
                for(int i = 0; i < sNode->num-1; ++i){
                    sNode->data[i] = sNode->data[i+1];
                    sNode->childPtr[i] = node->childPtr[i+4];
                    node->childPtr[i+4] = NULL;
                    sNode->childPtr[i]->parentPtr = sNode;
                }
                (sNode->num)--;
                (sNode->numInteger)--;
            }
            
            // insert s_data to sNode
            bool inserted = 0;
            /*
             TODO
             */
            string temp = s_data;
            for(int i = sNode->numInteger; i < sNode->num; i++){
                if(strcmp((*(string*)sNode->data[i]).c_str(), temp.c_str()) > 0){
                    string tmp = temp;
                    temp = *(string*)(sNode->data[i]);
                    delete (int*)sNode->data[i];
                    sNode->data[i] = new string(tmp);
                }
            }
            sNode->data[(sNode->num)] = new string(temp);
            (sNode->num)++;
            inserted = 1;
        }
        
        // add median and pointer to sNode to parent node
        if(pNode == NULL){
            // if splitted node is the root
            // make a empty node and link it to parent pointer of node
            root = new BPNode();
            if(medType == IMED){
                root->data[0] = new int(i_med);
                (root->numInteger)++;
            }
            else{
                root->data[0] = new string(s_med);
            }
            (root->num)++;
            root->childPtr[0] = node;
            root->childPtr[1] = sNode;
            node->parentPtr = root;
            sNode->parentPtr = root;
            root->set_leaf(NONLEAF);
        }
        else if(pNode->is_full() == UNFULL){
            // if parent node has room for a new data
            int medPos = 0;     // position that median will be inserted
            bool determined = 0;
            for(int i = 0; i < pNode->num; ++i){
                if(pNode->childPtr[i] == node){
                    medPos = i;
                    determined = 1;
                    break;
                }
            }
            if(determined == 0){
                medPos = pNode->num;
                determined = 1;
            }
            
            for(int i = pNode->num; i > medPos; --i){
                pNode->childPtr[i+1] = pNode->childPtr[i];
                pNode->data[i] = pNode->data[i-1];
            }
            pNode->childPtr[medPos+1] = sNode;
            sNode->parentPtr = pNode;
            if(medType == IMED){
                pNode->data[medPos] = new int(i_med);
                (pNode->numInteger)++;
            }
            else{
                pNode->data[medPos] = new string(s_med);
            }
            (pNode->num)++;
        }
        else{
            // if parent node does "NOT" have room for a new data
            if(medType == IMED){
                // TODO
                /*BPNode* temp = this->split_node(pNode, BULK, i_med);
                 int det = 0;
                 for(int i = 0; i < temp->numInteger; i++){
                 if(*(int*)(temp->data[i]) == i_med){
                 det = 1;
                 for(int j = 2; j > i+1; j--){
                 temp->childPtr[j] = temp->childPtr[j-1];
                 }
                 temp->childPtr[i+1] = sNode;
                 break;
                 }
                 }
                 for(int i = 0; i < pNode->numInteger; i++){
                 if(*(int*)(pNode->data[i]) == i_med){
                 det = 1;
                 BPNode* mingu = pNode->childPtr[3];
                 for(int j = 3; j > i+1; j--){
                 pNode->childPtr[j] = pNode->childPtr[j-1];
                 }
                 pNode->childPtr[i+1] = sNode;
                 for(int j = 2; j > 0; j--){
                 temp->childPtr[j] = temp->childPtr[j-1];
                 }
                 temp->childPtr[0] = mingu;
                 break;
                 }
                 }
                 
                 if(det == 0){
                 pNode->childPtr[3] = node;
                 for(int i = 2; i > 0; i++){
                 temp->childPtr[i] = temp->childPtr[i-1];
                 }
                 temp->childPtr[0] = sNode;
                 }
                 
                 //Assign parentPtr of all of childPtr
                 for(int i = 0; i < temp->num; i++){
                 temp->childPtr[i]->parentPtr = temp;
                 }
                 for(int i = 0; i < pNode->num; i++){
                 pNode->childPtr[i]->parentPtr = pNode;
                 }*/
                int ming = 0;
                for(int i = 0; i <= CAPACITY; i++){
                    if(pNode->childPtr[ming] != node)   ming++;
                    else    break;
                }
                if(ming < 3){
                    BPNode* temp = this->split_node(pNode, SINGLY, i_med);
                    sNode->parentPtr = pNode;
                    for(int i = 3; i > ming; --i){
                        pNode->childPtr[i+1] = pNode->childPtr[i];
                    }
                    pNode->childPtr[ming + 1] = sNode;
                    sNode->parentPtr = pNode;
                    temp->childPtr[2] = temp->childPtr[1];
                    temp->childPtr[1] = temp->childPtr[0];
                    temp->childPtr[0] = pNode->childPtr[4];
                    pNode->childPtr[4] = NULL;
                }
                
                else if(ming == 3){
                    sNode->parentPtr = split_node(pNode, SINGLY, i_med);
                    for(int i = 5; i > ming; --i){
                        sNode->parentPtr->childPtr[i-3] = sNode->parentPtr->childPtr[i-4];
                    }
                    sNode->parentPtr->childPtr[ming-3] = sNode;
                    sNode->parentPtr->childPtr[ming-3]->parentPtr = sNode->parentPtr;
                    
                }
                else{
                    BPNode* temp = this->split_node(pNode, SINGLY, i_med);
                    for(int j = 2; j > ming-3; j--){
                        temp->childPtr[j] = temp->childPtr[j-1];
                    }
                    temp->childPtr[ming-3] = sNode;
                    sNode->parentPtr = temp;
                    node->parentPtr = temp;
                }
                
            }
            else{
                // TODO
                /*BPNode* temp = this->split_node(pNode, BULK, s_med);
                 int det = 0;
                 for(int i = temp->numInteger; i < temp->num; i++){
                 if(*(string*)(temp->data[i]) == s_med){
                 for(int j = 2; j > i+1; j--){
                 temp->childPtr[j] = temp->childPtr[j-1];
                 }
                 temp->childPtr[i+1] = sNode;
                 det = 1;
                 break;
                 }
                 }
                 for(int i = pNode->numInteger; i < pNode->num; i++){
                 if(*(string*)(pNode->data[i]) == s_med){
                 BPNode* mingu = pNode->childPtr[3];
                 for(int j = 3; j > i+1; j--){
                 pNode->childPtr[j] = pNode->childPtr[j-1];
                 }
                 pNode->childPtr[i+1] = sNode;
                 for(int j = 2; j > 0; j--){
                 temp->childPtr[j] = temp->childPtr[j-1];
                 }
                 temp->childPtr[0] = mingu;
                 det = 1;
                 break;
                 }
                 }
                 
                 if(det == 0){
                 pNode->childPtr[3] = node;
                 for(int j = 2; j > 0; j--){
                 temp->childPtr[j] = temp->childPtr[j-1];
                 }
                 temp->childPtr[0] = sNode;
                 }
                 
                 ////Assign parentPtr of all of childPtr
                 for(int i = 0; i < temp->num; i++){
                 temp->childPtr[i]->parentPtr = temp;
                 }
                 for(int i = 0; i < pNode->num; i++){
                 pNode->childPtr[i]->parentPtr = pNode;
                 }*/
                int ming = 0;
                for(int i = 0; i <= CAPACITY; i++){
                    if(pNode->childPtr[ming] != node)   ming++;
                    else    break;
                }
                if(ming < 3){
                    BPNode* temp = this->split_node(pNode, SINGLY, s_med);
                    sNode->parentPtr = pNode;
                    for(int i = 3; i > ming; --i){
                        pNode->childPtr[i+1] = pNode->childPtr[i];
                    }
                    pNode->childPtr[ming + 1] = sNode;
                    sNode->parentPtr = pNode;
                    temp->childPtr[2] = temp->childPtr[1];
                    temp->childPtr[1] = temp->childPtr[0];
                    temp->childPtr[0] = pNode->childPtr[4];
                    pNode->childPtr[4] = NULL;
                }
                else if(ming == 3){
                    sNode->parentPtr = split_node(pNode, SINGLY, s_med);
                    for(int i = 5; i > ming; --i){
                        sNode->parentPtr->childPtr[i-3] = sNode->parentPtr->childPtr[i-4];
                    }
                    sNode->parentPtr->childPtr[ming-3] = sNode;
                    sNode->parentPtr->childPtr[ming-3]->parentPtr = sNode->parentPtr;
                    
                }
                else{
                    BPNode* temp = this->split_node(pNode, SINGLY, s_med);
                    for(int j = 2; j > ming-3; j--){
                        temp->childPtr[j] = temp->childPtr[j-1];
                    }
                    temp->childPtr[ming-3] = sNode;
                    sNode->parentPtr = temp;
                    node->parentPtr = temp;
                }
                
            }
        }
    }
    // split_node called by bulk_loading
    // split node 4/2
    else{
        // move data[4] of node to data[0] of sNode
        // remove data[4] of node by decrease num of node
        // set i_med
        sNode->data[0] = node->data[4];
        (node->num)--;
        (sNode->num)++;
        if(node->numInteger >= CAPACITY){
            // median will be integer
            medType = IMED;
            (node->numInteger)--;
            (sNode->numInteger)++;
            i_med = *(int*)(sNode->data[0]);
        }
        else{
            // median will be string
            medType = SMED;
            s_med = *(string*)(sNode->data[0]);
        }
        
        // insert i_data to sNode;
        // s_data is always inserted at the end
        sNode->data[sNode->num] = new string(s_data);
        (sNode->num)++;
        
        // if splitted node is "not a leaf node"
        if(node->is_leaf() == NONLEAF){
            
            //delete data[0] of sNode
            
            delete (int*)sNode->data[0];
            
            sNode->data[0] = sNode->data[1];
            (sNode->num)--;
            sNode->numInteger = 0;
            sNode->childPtr[0] = node->childPtr[5];
            node->childPtr[5] = NULL;
            sNode->childPtr[0]->parentPtr = sNode;
        }
        
        // add median and pointer to sNode to parent node
        if(pNode == NULL){
            // if splitted node is the root
            // make a empty node and link it to parent pointer of node
            root = new BPNode();
            if(medType == IMED){
                root->data[0] = new int(i_med);
                (root->numInteger)++;
            }
            else{
                root->data[0] = new string(s_med);
            }
            (root->num)++;
            root->childPtr[0] = node;
            root->childPtr[1] = sNode;
            node->parentPtr = root;
            sNode->parentPtr = root;
            root->set_leaf(NONLEAF);
        }
        else if(pNode->is_full() == UNFULL){
            // if parent node has room for a new data
            pNode->childPtr[pNode->num+1] = sNode;
            sNode->parentPtr = pNode;
            if(medType == IMED){
                pNode->data[pNode->num] = new int(i_med);
                (pNode->numInteger)++;
            }
            else{
                pNode->data[pNode->num] = new string(s_med);
            }
            (pNode->num)++;
            pNode->set_leaf(NONLEAF);
        }
        else{
            // if parent node does "NOT" have room for a new data
            if(medType == IMED){
                // TODO
                BPNode* temp = this->split_node(pNode, BULK, i_med);
                temp->childPtr[temp->num] = sNode;
                int determined = 0;
                for(int i = 0; i < pNode->num; i++){
                    if(typeid(pNode->data[i]) == typeid(sNode->data[0])){
                        if(pNode->data[i] == sNode->data[0]){
                            determined = 1;
                        }
                    }
                }
                if(determined == 1)     sNode->parentPtr = pNode;
                else if(determined == 0)    sNode->parentPtr = temp;
            }
            else{
                // TODO
                BPNode* temp = this->split_node(pNode, BULK, s_med);
                temp->childPtr[temp->num] = sNode;
                int determined = 0;
                for(int i = 0; i < pNode->num; i++){
                    if(typeid(pNode->data[i]) == typeid(sNode->data[0])){
                        if(pNode->data[i] == sNode->data[0]){
                            determined = 1;
                        }
                    }
                }
                if(determined == 1)     sNode->parentPtr = pNode;
                else if(determined == 0)    sNode->parentPtr = temp;
            }
        }
    }
    
    if(node->is_leaf() == LEAF){
        sNode->childPtr[CAPACITY] = node->childPtr[CAPACITY];
        node->childPtr[CAPACITY] = sNode;
    }
    return sNode;;
}

void BPTree::traverse(){
    BPNode* BPN = root;
    // TODO
    
    //BPN is most left leaf node
    while(BPN->isLeaf == NONLEAF){
        BPN = BPN->childPtr[0];
    }
    
    //print all leaf nodes
    while(BPN != NULL){
        for(int i = 0; i <= BPN->numInteger - 1; i++){
            cout<<(*(int*)BPN->data[i])<<" ";
        }
        for(int i = BPN->numInteger; i <= BPN->num - 1; i++){
            cout<<(*(string*)BPN->data[i]).c_str()<<" ";
        }
        BPN = BPN->childPtr[CAPACITY];
    }
}

void BPTree::h_print(BPNode* BPN){
    if(BPN == NULL) return;
    queue<BPNode*> q;
    q.push(BPN);
    while(q.empty() == false){
        int nodeCount = q.size();
        while(nodeCount > 0){
            BPNode* node = q.front();
            node->print();
            q.pop();
            int i = 0;
            //if(node->is_leaf() == NONLEAF){
            //for(int i = 0; i < node->num + 1; ++i){
            while(node->childPtr[i] != NULL){
                q.push(node->childPtr[i]);
                i++;
            }
            //}
            nodeCount--;
        }
        cout<<endl;
    }
}

BPNode* BPTree::get_root(){
    return root;
}
