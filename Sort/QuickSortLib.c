/*
QuickSortLib.h

void Swap(int* a, int* b);
void QuickSort(int* arr, int left, int right);
void QuickSort2(int* arr, int left, int right);
void QuickSort3(int* arr, int left, int right); //fastest
*/

void Swap(int* a, int* b){
    int tmp = *a;
    *a = *b;
    *b = tmp;
}

void QuickSort(int* arr, int left, int right){
    if(left >= right){
        return;
    }
    
    int pivot = arr[right];
    int i = left, j = right - 1;
    
    while(i < j){
        while(arr[i] < pivot && i < j){
            ++i;
        }
        while(arr[j] >= pivot && i < j){
            --j;
        }
        Swap(&arr[i], &arr[j]);
    }
    
    if(arr[i] >= pivot){
        Swap(&arr[i], &arr[right]);
    }else{
        ++i;
    }
    
    if(i){
        QuickSort(arr, left, i - 1);
    }
    QuickSort(arr, i + 1, right);
}

void QuickSort2(int* arr, int left, int right){
    if(left >= right){
        return;
    }
    
    int pivot = arr[left];
    int i = left + 1, j = right;
    
    while(i < j){
        while(arr[i] < pivot && i < j){
            ++i;
        }
        while(arr[j] >= pivot && i < j){
            --j;
        }
        Swap(&arr[i], &arr[j]);
    }
    
    if(arr[i] >= pivot){
        Swap(&arr[--i], &arr[left]);
    }else{
        Swap(&arr[i], &arr[left]);
    }
    
    if(i){
        QuickSort2(arr, left, i - 1);
    }
    QuickSort2(arr, i + 1, right);
}


//the fastest
//但不確定是否沒bug
void QuickSort3(int *data, int left, int right)
{
    if (left >= right) { 
        return; 
    }
    int pivot = data[left];
    int i = left + 1;
    int j = right;

    while (1){
        while (i <= right){
            if (data[i] >= pivot){
                break;
            }
            ++i;
        }

        while (j > left){
            if (data[j] < pivot){
                break;
            }
            --j;
        }

        if (i > j) { 
            break; 
        }
        Swap(&data[i], &data[j]);
    }

    Swap(&data[left], &data[j]);

    QuickSort3(data, left, j - 1);
    QuickSort3(data, j + 1, right);
}
