#include "tseitinTransformer.h"

TseitinTransformer::TseitinTransformer(TreeNode *root): formulaRoot{root} {}

int TseitinTransformer::transSubformula(TreeNode* subRoot) {
  // your code starts here
  if (subRoot == nullptr) {return 0;}
  if (varIdCounter==1){
    varIdTable[subRoot -> getContent()]=varIdCounter;
    std::vector<int> v1;
    v1.push_back(varIdCounter);
    cnf.push_back(v1);
  }

  if(subRoot-> getContent()!="+" && subRoot-> getContent()!="*" && subRoot-> getContent()!="-" ){
    //define two vars for each child
    //std::cout << subRoot -> getContent();
    if(varIdTable.count(subRoot -> getContent())==0){//var not in map
      varIdTable[subRoot -> getContent()]=varIdCounter++;
      return varIdTable[subRoot -> getContent()];
    }
    else if(varIdTable.count(subRoot -> getContent())==1){//var already in map
      return varIdTable[subRoot -> getContent()];
  }
  }
  else{
    // if(varIdTable.count(subRoot -> getContent()) == 1){
    //   varIdCounter++;
    // }
    // else {
    int current_id = varIdCounter;
    varIdTable[subRoot -> getContent()]=varIdCounter++;
    // }
    
    int var1= transSubformula(subRoot->getLeftChild());
    int var2=transSubformula(subRoot-> getRightChild());
    if(subRoot -> getContent()=="+"){
      addOrEq(current_id,var1,var2);
      return current_id;
    }
    if(subRoot -> getContent()=="*"){ 
      addAndEq(current_id,var1,var2);
      return current_id;
    }
    if(subRoot -> getContent()=="-"){ 
      addNegEq(current_id,var1);
      return current_id;
    }
  }
  return 0;
}

void TseitinTransformer::addNegEq(int curID, int childID) {
  // your code starts here
  //[-curID,-childId] AND [curID, child id]
     std::vector<int> v1;
     v1.push_back(-curID);
     v1.push_back(-childID);
     cnf.push_back(v1);
     std::vector<int> v2;
     v2.push_back(curID);
     v2.push_back(childID);
     cnf.push_back(v2);

}

void TseitinTransformer::addOrEq(int curID, int leftID, int rightID) {
  // your code starts here
  //[-curId,leftId,rightID] AND [-leftID,curID]AND[-rightID,CurID][CurID]
     std::vector<int> v1;
     v1.push_back(-curID);
     v1.push_back(leftID);
     v1.push_back(rightID);
     cnf.push_back(v1);

     std::vector<int> v2;
     v2.push_back(-leftID);
     v2.push_back(curID);
     cnf.push_back(v2);

     std::vector<int> v3;
     v3.push_back(-rightID);
     v3.push_back(curID);
     cnf.push_back(v3);
   

}

void TseitinTransformer::addAndEq(int curID, int leftID, int rightID) {
  // your code starts here
  std::vector<int> v1;
   v1.push_back(-curID);
   v1.push_back(leftID);
    cnf.push_back(v1);

    std::vector<int> v2;
     v2.push_back(-curID);
     v2.push_back(rightID);
     cnf.push_back(v2);

     std::vector<int> v3;
     v3.push_back(-leftID);
     v3.push_back(-rightID);
     v3.push_back(curID);
     cnf.push_back(v3);

}

std::vector<std::vector<int>> TseitinTransformer::transform() {
  // your code starts here
  transSubformula(formulaRoot);
  return cnf;
}

std::string TseitinTransformer::cnfString() const {
  std::string result = "";
  // your code starts here
  // std::cout << cnf[0][0] << std::endl;
  for(int i=0;i<cnf.size();i++){
    std::cout<<"[";
    for (int j=0;j<cnf[i].size();j++){
      std::cout<<cnf[i][j];
      if (j != cnf[i].size() - 1) {std::cout << ",";};      
    }
    std::cout<<"]";
  }
  std::cout << std::endl;
  return result;
}

unsigned int TseitinTransformer::getVarNum() const {
  // your code starts here
  return varIdCounter;
}
