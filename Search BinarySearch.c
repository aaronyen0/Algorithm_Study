/**
 * 假設arr[]為遞增數列
 * 從arr[left:right]尋找num
 */

int BinarySearch(int* arr, int left, int right, int num){
	int mid;
	while (left <= right){
		mid = (right + left) >> 1;
		if (arr[mid] == num){
			return mid;
		}
		 
		if (arr[mid] > num){
			right = mid - 1;
		}else{
			left = mid + 1;
		}
	}
	return -1;
}
