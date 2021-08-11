#ifndef VMEM_H
#define VMEM_H

#include <deque>
#include <map>

#define VMEM_RAND_FACTOR 91827349653
// reserve 1MB of space
#define VMEM_RESERVE_CAPACITY 1048576

class VirtualMemory
{
    private:
        uint32_t page_size;
        std::deque<uint64_t> ppage_free_list;

        std::map<std::pair<uint32_t, uint64_t>, uint64_t> vpage_to_ppage_map;
        std::map<std::tuple<uint32_t, uint64_t, uint32_t>, uint64_t> page_table;

    public:
        const uint32_t pt_levels;
        // capacity and pg_size are measured in bytes, and capacity must be a multiple of pg_size
        VirtualMemory(uint32_t number_of_cpus, uint64_t capacity, uint64_t pg_size, uint32_t page_table_levels, uint64_t random_seed);
        uint64_t va_to_pa(uint32_t cpu_num, uint64_t vaddr);
        uint64_t get_pte_pa(uint32_t cpu_num, uint64_t vaddr, uint32_t level);
};

#endif

