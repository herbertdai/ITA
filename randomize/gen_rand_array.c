
/*
 * gen_rand_array.c
 * @date 20130622
 * @auther dwy
 */


int randomize_in_place(int* Array, int lenth)
{
    int temp = 0;
    int i = 0;
    int random_index = 0;

    srand((int)time(0));

    for (i=0; i<lenth; i++){
        Array[i] = i;
    }

    for (i=0; i<lenth; i++){
        //Swap a[i] and a[random(i,n)]
        temp = Array[i];
        random_index = (int)(rand() % (lenth - i));
        Array[i] = Array[random_index];
        Array[random_index] = temp;
    }
    return 1;

}

int randomize_maxnum(int* Array, int lenth, int maxNum){
    int temp = 0;
    int i = 0;
    int random_index = 0;

    srand((int)time(0));

    for (i=0; i<lenth; i++){
        Array[i] = (int)(rand() % maxNum);
    }

    for (i=0; i<lenth; i++){
        //Swap a[i] and a[random(i,n)]
        temp = Array[i];
        random_index = (int)(rand() % (lenth - i));
        Array[i] = Array[random_index];
        Array[random_index] = temp;
    }
    return 1;
}
