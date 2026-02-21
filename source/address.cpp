#include "address.h"
#include <iostream>

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

Address::Address(Address * address_prev, std::ifstream & file, int * status)
{
    set_address_prev(address_prev);
    set_address_next(nullptr);
    (*status) = read_from_file(file);
}

Address & Address::operator=(const Address & address_copy)
{
    if(&address_copy != this)
    {
        // Пусть при присваивании копируются только эти поля, а указатели не копируются
        __sity = address_copy.__sity;
        __street = address_copy.__street;
        __home = address_copy.__home;
        __flat = address_copy.__flat;
    }

    return *this;
}
int Address::read_from_file(std::ifstream & file)
{
    if(!(file >> __sity))
    {
        return -1;
    }

    if(!(file >> __street))
    {
        return -2;
    }

    if(!(file >> __home))
    {
        return -3;
    }

    if(!(file >> __flat))
    {
        return -4;
    }

    return 0;
}

int Address::write_to_file(std::ofstream & file)
{
    file << __sity << ", " << __street << ", " << __home << ", " << __flat << ((__address_next != nullptr) ? "\n" : "");
    return 0;
}

void Address::set_address_prev(Address * address_prev)
{
    __address_prev = address_prev;
}

void Address::set_address_next(Address * address_next)
{
    __address_next = address_next;
}

Address * Address::get_address_prev(void)
{
    return __address_prev;
}

Address * Address::get_address_next(void)
{
    return __address_next;
}

std::string & Address::sity_get(void)
{
    return __sity;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

Addresses::Addresses(const char * input_file_path, int * status)
{
    std::ifstream file(input_file_path);
    if(!file.is_open())
    {
        (*status) = -1000;
        return;
    }

    if(!(file >> __count))
    {
        (*status) = -1001;
        file.close();
        return;
    }

    __addresses_head = nullptr;
    Address * address_prev = nullptr;
    while(!file.eof())
    {
        Address * address_cur = new Address(address_prev, file, status);
        if((*status) != 0)
        {
            file.close();
            return;
        }

        if(address_prev != nullptr)
        {
            address_prev->set_address_next(address_cur);
        }

        if(__addresses_head == nullptr)
        {
            __addresses_head = address_cur;
        };
        __addresses_tail = address_cur;
        
        address_prev = address_cur;
    }

    file.close();

}

Addresses::~Addresses(void)
{
    Address * address_cur = __addresses_tail;
    while(address_cur != nullptr)
    {
        Address * address_prev = address_cur->get_address_prev(); 
        delete address_cur;
        address_cur = address_prev;
    }
}

void Addresses::sort(void)
{
    Address * address_cur = __addresses_head;
    while(address_cur != nullptr)
    {
        Address * address_cmp = address_cur->get_address_next();
        while(address_cmp != nullptr)
        {
            if(address_cur->sity_get() > address_cmp->sity_get())
            {
                address_swap(address_cur, address_cmp); 
            }
            address_cmp = address_cmp->get_address_next();
        }
        address_cur = address_cur->get_address_next();
    }
}

int Addresses::output(const char * output_file_path)
{
    std::ofstream file(output_file_path);
    if(!file.is_open())
    {
        return -1;
    }

    file << __count << "\n";

    Address * address_cur = __addresses_head;
    while(address_cur != nullptr)
    {
        if(address_cur->write_to_file(file) != 0)
        {
            file.close();
            return - 2;
        }

        address_cur = address_cur->get_address_next();
    }

    file.close();
    return 0;
}

void Addresses::address_swap(Address * a1, Address * a2)
{
    Address tmp = (*a1);
    (*a1) = (*a2);
    (*a2) = tmp;
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////