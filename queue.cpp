#include <iostream>
#include <math.h>
using namespace std;
struct Queue {
    int length;
    int *data;
    int start;
    int end;
    int depth;
};

Queue newQueue(int l){
    if (l < 0) throw - 1;
    Queue nq;
    nq.length = l;
    nq.start = 0;
    nq.end = -1;
    nq.depth = 0;
    nq.data = l > 0 ? new int[l] : NULL;
    return nq;
}

void deleteQueue(Queue& q) {
    if (q.data != NULL) delete[] q.data;
    q = newQueue(0);
}

void resizeQueue(Queue& q, int d = 10){
    if (q.length + d < q.depth) throw - 2;
    Queue nq = newQueue(q.length + d);
    int *pt = new int[q.length + d];
    for (int i = 0; i < q.depth; ++i){
        pt[i] = q.data[(q.start + i) % q.length];
    }
    q.length += d;
    q.start = 0; q.end = q.depth - 1;
    delete[] q.data;
    q.data = pt;
}

void copyQueue(Queue& qd, const Queue& qs){
    if (qd.length < qs.depth){
        resizeQueue(qd, qs.depth - qd.length);
    }
    for (int i = 0; i < qs.depth; ++i){
        qd.data[i] = qs.data[(qs.start + i) % qs.length];
    }
    qd.start = 0; qd.end = qs.depth - 1; qd.depth = qs.depth;
}

void pushQueue(Queue& q, int l){
    if (q.length == q.depth) resizeQueue(q);
    q.depth++;
    q.end++;
    if (q.end == q.length){
        q.end = 0;
    }
    q.data[q.end] = l;
}

bool isEmptyQueue(const Queue& q){
    return ((q.data == NULL) or (q.depth == 0));
}

int pullQueue (Queue& q){
    if (isEmptyQueue(q)) throw -1;
    int l = q.data[q.start];
    q.depth--;
    q.start++;
    if (q.start == q.length) q.start = 0;
    return l;
}

int topQueue(const Queue& q){
    if (isEmptyQueue(q)) throw - 3;
    return q.data[q.start];
}

int main() {
    Queue q1;
    Queue q2;
    Queue q3;
    Queue q4;
    q1 = newQueue(0);
    q2 = newQueue(0);
    q3 = newQueue(0);
    q4 = newQueue(0);
    for (int i = 0; i < 10; ++i){
        pushQueue(q1,i);
    }
// копируем 1 в 4 и выводим на экран первую очередь
    while (!isEmptyQueue(q1)){
        pushQueue(q4,topQueue(q1));
        pushQueue(q3,topQueue(q1));
        cout << topQueue(q1) << ' ';
        pullQueue(q1);
    }
    
    while (!isEmptyQueue(q3)){
        pushQueue(q1,topQueue(q3));
        pullQueue(q3);
    }
    deleteQueue(q3);
}