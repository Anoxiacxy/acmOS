// 提示：把元数据页加入到空闲池子里
void _buddy_return_page(page_t* page) {
    // TODO: make merge here
    // Suggested: 4 LoCs
    page->flags = BD_PAGE_FREE;
    bd_lists[page->orders].nr_free++;
    list_add(&page->list_node, &bd_lists[page->orders].list_head);
}

// 这个函数可以修改
void _buddy_get_specific_page(page_t* page) {
    page->flags |= BD_PAGE_IN_USE;
    bd_lists[page->orders].nr_free--;
    list_del(&page->list_node);
}

void _buddy_clear_flag(page_t* page) { page->flags = 0; }

// 提示：buddy伙伴页的元数据位于整个内存可分配区域的最前面
// 该函数给出一个buddy伙伴页的元数据指针
// 返回元数据所指向的页是全局从数据区开始的第几个页
uint64 _buddy_get_page_idx(page_t* page) { 
    return ((uint64) page - bd_meta.meta_head) / sizeof(page_t); 
}

// 提示：请仔细阅读kfree函数的代码
uint64 _buddy_get_area_idx(void* head) { 
    return ((uint64) head - bd_meta.data_head) / PGSIZE;
}

// 提示：给出一个全局页的下标，返回这个页的元数据指针
page_t* _buddy_idx_get_page(uint64 idx) {
    return (page_t*)(bd_meta.meta_head + idx * sizeof(page_t));
}

// 提示：给出一个页的元数据指针，找到这个页的buddy页的元数据指针
// 注意利用buddy页的一些性质
page_t* _buddy_get_buddy_page(page_t* page) {
    uint64 idx = _buddy_get_page_idx(page);
    idx ^= 1L << page->orders;
    if (idx < bd_max_entries) 
        return _buddy_idx_get_page(idx);
    else
        return NULL;
}

// 提示：给出一个buddy页的元数据，将这个页分裂成至少出现1个target_order的函数
void _buddy_split_page(page_t *original_page, uint64 target_order){
    _buddy_get_specific_page(original_page);
    while (original_page->orders > target_order) {
        original_page->orders--;
        page_t *buddy_page = _buddy_get_buddy_page(original_page);
        buddy_page->orders = original_page->orders;
        _buddy_clear_flag(buddy_page);
        _buddy_return_page(buddy_page);
    }
    _buddy_return_page(original_page);
}

// 提示：分配一个order为order的页
page_t *_buddy_alloc_page(uint64 order){
    // Suggested: 13 LoCs
    for (uint64 o = order; o < bd_max_size; o++) {
        if (bd_lists[o].nr_free > 0) {
            page_t* page = (page_t*) bd_lists[o].list_head.next;
            _buddy_split_page(page, order);
            _buddy_get_specific_page(page);
            _buddy_clear_flag(page);
            return page;
        }
    }
    return NULL;
}

// 这个函数可以修改
void buddy_free_page(page_t* page) {
    page_t* current_page = page;
    for (; current_page->orders < bd_max_size; ++current_page->orders) {
        page_t* buddy_page = _buddy_get_buddy_page(current_page);
        if (buddy_page == NULL) break;
        if ((!(buddy_page->flags & BD_PAGE_FREE))) break;
        if (buddy_page->orders != current_page->orders) break;
        page_t* to_be_released = NULL;
        if(_buddy_get_page_idx(current_page) > _buddy_get_page_idx(buddy_page))
            to_be_released = current_page;
        else 
            to_be_released = buddy_page;
        _buddy_get_specific_page(to_be_released);
        _buddy_clear_flag(to_be_released);
        if(_buddy_get_page_idx(current_page) > _buddy_get_page_idx(buddy_page))
            current_page = buddy_page;
    }
    _buddy_return_page(current_page);
}
