/* @Author
Student Name: Emre Yurdakul
Student ID : 150190030
Date: 10.11.2021 */

#include <iostream>
#include <stdio.h>
#include <string.h>

#include "linkedList.h"

using namespace std;

int wagoncurrid=1;

void Train::create(){
    head = NULL;
}; 

void wagonNode::set_wag_next(wagonNode* next){
    this->next=next;
}

wagonNode* wagonNode::get_wag_next(){
    return this->next;
}

void materialNode::set_mat_next(materialNode* next){
    this->next=next;
}

materialNode* materialNode::get_mat_next(){
    return this->next;
}

void wagonNode::wagonIdd(int a){
    this->wagonId = a;
    wagoncurrid+=1;
}


///////

materialNode* finder(char material, wagonNode* head){//this function find specific material in the next wagon
    
        wagonNode* checkWagon = head;
        materialNode* checkMat = checkWagon->material;
        materialNode* checkMat2 = checkWagon->material;

        int checkOkey=0;
        int checkOkey2=0;
///////////////////////////////////////////////////////////////////////////
        while(checkMat!=NULL){

            if(checkMat->id==material){
                checkOkey=1;

                if(checkMat->weight==2000){

                    if(checkWagon->next==NULL){
                        checkWagon->set_wag_next(new wagonNode());
                        checkWagon = checkWagon->get_wag_next();

                        checkWagon->wagonIdd(wagoncurrid);
                        checkWagon->material= new materialNode();
                        
                        checkMat = checkWagon->material;
                        checkMat->id = material;
                        return checkMat;
                    }
                    else{
                        checkWagon=checkWagon->next;

                        while(checkMat!=NULL){

                            if(checkMat->id==material){
                                checkOkey2=1;
                                return checkMat;
                            }

                            checkMat = checkMat->next;
                        }
                        while(checkMat2->next!=NULL){
                            checkMat2 = checkMat2->next;
                            }

                        if(checkOkey2==0){
                            checkMat2->set_mat_next(new materialNode());
                            checkMat2 = checkMat2->get_mat_next();
                            checkMat2->id = material;
                            return checkMat2;
                        }
                    }
                }
                else{
                   return checkMat;
                }
            }

                checkMat = checkMat->next;
     
     }
//////////////////////////////////////////////////////////////////////////////
        while(checkMat2->next!=NULL){
            checkMat2 = checkMat2->next;
        }
        
        if(checkOkey==0){
            checkMat2->set_mat_next(new materialNode());
            checkMat2 = checkMat2->get_mat_next();
            checkMat2->id = material;
            return checkMat2;
        }
        else{
            return checkMat2 ;
        }

}

//////
materialNode* finderMAT(char material, wagonNode* head){//this function finds specific material in the current wagon
    
        wagonNode* checkWagon = head;
        materialNode* checkMat = checkWagon->material;

        while (checkMat!=NULL)
        {
            if(checkMat->id==material){
                break;
            }
            checkMat = checkMat->next;
        }
        return checkMat;
}
        
//////

void reorder(wagonNode* head){//this function sorts material alphabetical order

    wagonNode* wg = head;

    while (wg!=NULL)
    {
        for(int i=0;i<3;i++){

            materialNode* first = wg->material;
            materialNode* sec = first->next;

            while(first != NULL && sec != NULL){

                char firstc = first->id;
                char secc = sec->id;

                int firsti= firstc;
                int seci= secc;
                
                if(firsti>seci){

                    char tmp = first->id;
                    int wgt = first->weight;

                    char s = sec->id;
                    int sgt = sec->weight;

                    first->id = s;
                    first->weight = sgt;

                    sec->id = tmp;
                    sec->weight = wgt;

                    first = first->next;
                    sec = sec->next; 
                    
                }
                else{
                    first = first->next;
                    sec = sec->next;
                }
                
            }
    }
    wg = wg->next;
}

}

//////

materialNode* lastMaterial(wagonNode* head, char material){ //this function finds specific material in the last wagon

    wagonNode* headW = head;
    wagonNode* tempW = headW;


    while(tempW->next!=NULL){

        materialNode* currNEXT = finder(material,tempW->next);

        if(currNEXT->weight==0){
            wagonNode* hadiW = tempW->next;
            materialNode* hadiM = hadiW->material;

            int checkk=0;
                            
            while (hadiM->next!=NULL && checkk==0)
            {
                if(hadiM->next->weight==0){
                    if(hadiM->next->next==NULL){
                        hadiM->next=NULL;
                        wagoncurrid -= 1;
                        break;
                    }
                    else{
                        hadiM->next = hadiM->next->next;
                        break;
                    }
                }
                hadiM = hadiM->next;
            }
                            
            break;
                            
        }
                        
        else{
                            
            tempW = tempW->next;
        }
    }
    materialNode* currN = finderMAT(material, tempW);
    return currN;

} 

//////

void deleteNullWag(wagonNode* head){//this function deletes material with zero weight

    wagonNode* wagon = head;

    while (wagon->next!=NULL)
    {
       materialNode* matnod = wagon->next->material;

       if(matnod->weight==0 && matnod->next==NULL){
           wagon->next=NULL;
           wagoncurrid-=1;
           break;
       }
       else if(matnod->weight==0 && matnod->next!=NULL){
           
           wagon->next->material = matnod->next;
       }

        
        wagon = wagon->next;
    }
    

}

/////

void deleteNullWag2(wagonNode* head){//this function checks first wagon and deletes material node

    wagonNode* wagon2=head;
    materialNode* mat2 = wagon2->material;
    int check = 0;

    while (mat2->next!=NULL)
    {
        if(mat2->next->weight==0){
            check =1;
            break;
        }
        mat2 = mat2->next;
                
    }

    if(check==1){

        if(mat2->next->next==NULL){
            mat2->next=NULL;
        }
        else{
            mat2->next=mat2->next->next;
        }
    }


}

/////

void adding(wagonNode* pw, materialNode* pn, int weight, char material){// this function adds the desired amount of weight to the requested material

    materialNode* mNode = pn;
    materialNode* mNode2 = pn;
    wagonNode* wNode = pw;

    int temp = mNode->weight + weight;
    int temp2 = mNode->weight + weight;
    int remain = (mNode->weight + weight) % 2000;

    int part = 0;

    while(temp2 >= 2000){

        part += 1;
        temp2 -= 2000;
    }

    if(temp<=2000){
        mNode->weight = temp;
    }

    else{
        mNode->weight = 2000;

        for(int i=1; i < part; i++){

            if(wNode->next==NULL){
                    wNode->set_wag_next(new wagonNode());
                    wNode = wNode->get_wag_next();

                    wNode->wagonIdd(wagoncurrid);
                    wNode->material= new materialNode();
                        
                    mNode = wNode->material;
                    mNode->id = material;
                    mNode->weight = 2000;
             }
            else{
                 wNode = wNode->next;
                 mNode2 = wNode->material;

                int c = 0;

                 while(mNode2->next!=NULL){
                    mNode2 = mNode2->next;
                }

                 if(c==0){
                    mNode2->set_mat_next(new materialNode());
                    mNode2 = mNode2->get_mat_next();
                    mNode2->id = material;
                    mNode2->weight = 2000;
                 }
                 

             }
         }

            if(wNode->next==NULL){
                wNode->set_wag_next(new wagonNode());
                wNode = wNode->get_wag_next();

                wNode->wagonIdd(wagoncurrid);
                wNode->material= new materialNode();
                        
                mNode = wNode->material;
                mNode->id = material;
                mNode->weight = remain;
            }
            else{

                if(remain!=0){
                    wNode = wNode->next;

                    mNode2 = wNode->material;

                    while(mNode2->next!=NULL){

                        mNode2 = mNode2->next;
                    }

                    mNode2->set_mat_next(new materialNode());
                    mNode2 = mNode2->get_mat_next();

                    mNode2->id = material;
                    mNode2->weight = remain;
                }

            }     

    }


}

//////

materialNode* matN;

void Train::addMaterial(char material, int weight){
        
        wagonNode* headW = head;
        

        if(headW==NULL){
            head = new wagonNode();
            headW = head;
            headW->wagonIdd(wagoncurrid);
            headW->material= new materialNode();
            matN= headW->material;
            matN->id = material;
            adding(headW, matN, weight, material);          
        }

        else{
            materialNode* currN = finder(material,headW);

            wagonNode* tempW = headW;

            while(true){

                if(currN->weight<2000){
                    break;
                }

                else{
                    currN = finder(material,tempW);

                    if(currN->weight<2000){
                        break;
                    }

                    if(tempW->next!=NULL){

                        tempW = tempW->next;

                    }
                }

            }
            adding(tempW, currN, weight, material);
        }

        reorder(headW);
        deleteNullWag(head);
}; 


void Train::deleteFromWagon(char material, int weight){
        
        wagonNode* headW = head;

        materialNode* currN = finder(material,headW);


        wagonNode* tempW = headW;

        while(true){

            if(currN->weight<2000){
                break;
            }

            else{
                currN = finder(material,tempW);

                if(currN->weight<2000 || currN==NULL){
                    break;
                }

                if(tempW->next!=NULL){

                    materialNode* check = tempW->next->material;
                    int noliy = 0;
                    while(check!=NULL){
                                    
                        if(check->id==material){
                            noliy = 1;
                        }
                        check = check->next;
                    }

                    if(noliy==1){
                        tempW = tempW->next;
                    }
                                
                }
            }

        }

        if(currN->weight-weight>0){

            currN->weight -= weight;
        }

        else{
            int tempWe = weight-currN->weight;;
            int partWe = 0;
            int remain;

            currN->weight=0;
            remain = tempWe % 2000;

            while (tempWe>=2000)
            {
                partWe++;
                tempWe -= 2000;
            }

            for(int i=0 ; i<partWe; i++){

                currN = lastMaterial(head,material);
                currN->weight = 0;

            }
            currN = lastMaterial(head,material);
            currN->weight -= remain;

        }
        deleteNullWag(head);

        deleteNullWag2(head);


        if(head->material->weight==0 && head->material->next==NULL){//check first wagon's first material node and delete
            head = NULL;
            }

        else if(head->material->weight==0 && head->material->next!=NULL){
            head->material= head->material->next;
        }  

};  


void Train::printWagon(){
    wagonNode* tempWagon = head;

    if(tempWagon == NULL){
            cout<<"Train is empty!!!"<<endl;
            wagoncurrid=1;
            return;
    }

    while(tempWagon != NULL){
        materialNode* tempMat = tempWagon->material;
        cout<<tempWagon->wagonId<<". Wagon:"<<endl; 
        while (tempMat != NULL){
            cout<<tempMat->id<<": "<<tempMat->weight<<"KG, "; 
            tempMat = tempMat->next;  
        }
        cout<<endl; 
        tempWagon = tempWagon->next;
    }
    cout<<endl;
}; 