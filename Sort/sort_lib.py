    def quick_sort(self, nums, left ,right):
        """
        離開while的條件只有當 i > j時
        nums[j] >= pivot
        包含j有可能剛好就是在left上自己跟自己交換
        """
        if left >= right:
            return
        
        pivot = nums[left]
        i = left + 1
        j = right
        
        while True:
            while i <= right:
                if nums[i] >= pivot:
                    break
                i += 1
                    
            while j > left:
                if nums[j] < pivot:
                    break
                j -= 1
                    
            if i > j:
                break
                
            nums[i], nums[j] = nums[j], nums[i]
            
        nums[left], nums[j] = nums[j], nums[left]
        
        self.quick_sort(nums, left, j-1)
        self.quick_sort(nums, j+1, right)
