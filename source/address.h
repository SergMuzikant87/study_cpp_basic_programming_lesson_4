#ifndef __INC_ADDRESS_H__
#define __INC_ADDRESS_H__

    #include <cstdint>
    #include <fstream>
    #include <string>

    class Address
    {
        private:
            Address * __address_prev;
            Address * __address_next;

            std::string __sity;
            std::string __street;
            uint16_t __home;
            uint16_t __flat;
            
        public:
            Address(Address * address_prev, std::ifstream & file, int * status);
            Address & operator=(const Address & addr);
            int read_from_file(std::ifstream & file);
            int write_to_file(std::ofstream & file);
     
            std::string & sity_get(void);
            void set_address_prev(Address * address_prev);
            void set_address_next(Address * address_next);
            Address * get_address_prev(void);
            Address * get_address_next(void);

    };

    class Addresses
    {
       
        private:
            Address * __addresses_head = nullptr;
            Address * __addresses_tail =  nullptr;
            
            uint32_t __count;

            void address_swap(Address * a1, Address * a2);
        
        public:
            Addresses(const char * input_file_path, int * status);
            ~Addresses(void);
            
            void sort(void);
            int output(const char * output_file_path);

    };

#endif