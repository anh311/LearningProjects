typedef struct {
    int res;
    int over;
    int termine[1000][2];
    int overlap[1000][2];
} MyCalendarTwo;


MyCalendarTwo* myCalendarTwoCreate() {
    MyCalendarTwo* cal = malloc(sizeof(MyCalendarTwo));
    cal->res=0;
    cal->over=0;
    return cal;
}

bool myCalendarTwoBook(MyCalendarTwo* obj, int startTime, int endTime) {
    for (int i= 0;i<obj->over; i++){
        if(startTime < obj->overlap[i][1] && endTime > obj->overlap[i][0] ){
            return false;
        }
    }
    for (int i= 0;i<obj->res; i++){
        if(startTime < obj->termine[i][1] && endTime > obj->termine[i][0]){
            if (startTime>obj->termine[i][0]){
                obj->overlap[obj->over][0]=startTime;
            }else{
                obj->overlap[obj->over][0]=obj->termine[i][0];
            }
            if (endTime>obj->termine[i][1]){
                obj->overlap[obj->over][1]=obj->termine[i][1];
            }else{
                obj->overlap[obj->over][1]=endTime;
            }
            obj->over++;
            
        }

    }
  
    obj->termine[obj->res][0]=startTime;
    obj->termine[obj->res][1]=endTime;
    obj->res++;
    return true;

}

void myCalendarTwoFree(MyCalendarTwo* obj) {
    free(obj);
}

/**
 * Your MyCalendarTwo struct will be instantiated and called as such:
 * MyCalendarTwo* obj = myCalendarTwoCreate();
 * bool param_1 = myCalendarTwoBook(obj, startTime, endTime);
 
 * myCalendarTwoFree(obj);
*/