typedef struct {
    int res;
    int termin[1000][2];

} MyCalendar;


MyCalendar* myCalendarCreate() {
    MyCalendar* Calendar= malloc(sizeof(MyCalendar));
    Calendar->res=0;
    return Calendar;
}

bool myCalendarBook(MyCalendar* obj, int startTime, int endTime) {
    for (int i = 0;i <obj->res;i++){
        if(obj->termin[i][0]<endTime && obj->termin[i][1]>startTime){
            return false;
        }
    }
        obj->termin[obj->res][0]=startTime;
        obj->termin[obj->res][1]=endTime;
        obj->res++;
        return true;

}

void myCalendarFree(MyCalendar* obj) {
    free(obj);
}

/**
 * Your MyCalendar struct will be instantiated and called as such:
 * MyCalendar* obj = myCalendarCreate();
 * bool param_1 = myCalendarBook(obj, startTime, endTime);
 
 * myCalendarFree(obj);
*/