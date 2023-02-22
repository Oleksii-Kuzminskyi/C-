#include "doubly_linked_list.h"
#include <cmath>


//private functions
void DLL::bubble_sort(int * ar, const int num)
{
    for (int i = 0; i < num; i++)
    {
        int max_index = i;

        /*(num - 1) --- to prevent stack smashing error,
         * when comparing ar[j] and ar[j + 1];
         *
         * (num - 1) - max_index --- reducing limit,
         * after each biggest element reaches the end.
        */
        for (int j = 0; j < (num - 1) - max_index; j++)
        {
            if (ar[j] > ar[j + 1])
            {
                int temp = ar[j];
                ar[j] = ar[j + 1];
                ar[j + 1] = temp;
            }
        }
    }
}
void DLL::select_sort(int * ar, const int num)
{
    for (int i = 0; i < num; i++)
    {
        int min = i;

        for (int j = i + 1; j < num; j++) if (ar[min] > ar[j]) min = j;

        int temp = ar[i];
        ar[i] = ar[min];
        ar[min] = temp;

    }

}
void DLL::insert_sort(int * ar, const int num)
{
    for (int i = 1; i < num; i++)
    {
        int sorted = i - 1;

        while (sorted > -1 && ar[sorted] > ar[sorted + 1])
        {
            int temp = ar[sorted];
            ar[sorted] = ar[sorted + 1];
            ar[sorted + 1] = temp;
            --sorted;
        }
    }

}

void DLL::internal_quick_sort(int * ar, int left, int right)
{
    if (left >= right) return;

    int pivot_location = partition(ar, left, right);
    internal_quick_sort(ar, left, pivot_location - 1);
    internal_quick_sort(ar, pivot_location, right);
}


int DLL::partition(int * ar, int left, int right)
{
    int pivot = ar[right];
    int current = 0;
    int swap_marker = -1;

    while (current <= right)
    {
        if (ar[current] > pivot) ++current;
        else
        {
            ++swap_marker;
            if (current > swap_marker) swap(ar[current], ar[swap_marker]);
            else ++current;
        }
    }
    return swap_marker;
}

// constructors, destrucror
DLL::DLL() : head(nullptr), tail(nullptr), elcount(0)
{

}

DLL::DLL(const int val) : elcount(0)
{
    head = new Node(val);
    tail = head;
    ++elcount;
}

DLL::DLL(const DLL & obj) : head(nullptr), tail(nullptr), elcount(0)
{
    if (obj.head != nullptr && obj.tail != nullptr) //if obj not empty
    {
        /*
         * obj contains at least one node if we ended up here,
         * so let's already allocate memory
         */
        Node * node_alloc = new Node(obj.head->data);
        ++elcount;

        head = node_alloc;
        tail = head;

        Node * temp = obj.head->next; //counter for parsing obj content

        while (temp != nullptr)
        {
            node_alloc = new Node(temp->data);
            ++elcount;
            node_alloc->prev = tail;
            tail->next = node_alloc;
            tail = node_alloc;
            temp = temp->next;
        }
        node_alloc = nullptr; //for more safety
    }
}

DLL::DLL(DLL && obj) : head(nullptr), tail(nullptr), elcount(0)
{
    head = obj.head;
    tail = obj.tail;
    elcount = obj.elcount;

    obj.head = obj.tail = nullptr;
    obj.elcount = 0;
}

DLL::~DLL()
{
    clear();
}

//operators
DLL & DLL::operator=(const DLL & obj)
{
    clear();

    if (obj.head != nullptr && obj.tail != nullptr)
    {
        Node * node_alloc = new Node(obj.head->data);
        ++elcount;

        head = node_alloc;
        tail = head;

        Node * temp = obj.head->next;

        while (temp != nullptr)
        {
            node_alloc = new Node(temp->data);
            ++elcount;
            node_alloc->prev = tail;
            tail->next = node_alloc;
            tail = node_alloc;
            temp = temp->next;
        }
    }

    return *this;
}

DLL & DLL::operator=(DLL && obj)
{
    clear();

    head = obj.head;
    tail = obj.tail;
    elcount = obj.elcount;

    obj.head = obj.tail = nullptr;
    obj.elcount = 0;

    return *this;
}

DLL operator+(const DLL & d1, const DLL & d2)
{
    DLL sum(d1);
    sum.merge(d2);
    return sum;
}

//modifying methods

/*
 * When pushing element in mid, e.g.
 * we want push '6' in mid in the list, that
 * contains ODD number of elements:
 *
 * 3->4->5 --- the result is: 3->6->4->5
*/
void DLL::push(const elem_pos where, const int element)
{
    if (head == nullptr && tail == nullptr)
    {
        head = new Node(element);
        ++elcount;
        tail = head;
    }
    else
    {
        if (where == FRONT)
        {
            Node * temp = new Node(element);
            ++elcount;
            temp->next = head;
            head->prev = temp;
            head = temp;
            temp = nullptr;
        }
        else if (where == MID)
        {
            // if inserting mid where only 1 element
            if (head == tail) push(DLL::BACK, element);
            else
            {
                int count = 1;
                Node * temp = head;
                while (count != (elcount / 2) + (elcount % 2))
                {
                    temp = temp->next;
                    ++count;
                }

                Node * alloc = new Node(element);
                ++elcount;
                temp->next->prev = alloc;
                alloc->prev = temp;
                alloc->next = temp->next;
                temp->next = alloc;
                alloc = temp = nullptr;
            }

        }
        else if (where == BACK)
        {
            Node * temp = new Node(element);
            ++elcount;
            temp->prev = tail;
            tail->next = temp;
            tail = temp;
            temp = nullptr;
        }
    }
}

/*
 * When popping element from mid in list, that
 * contains EVEN number of elements:
 *
 * 3->4->5->6 --- the result is: 3->5->6
 *
 * It works that way, if we have 2 elements:
 * 3->4 --- 4.
*/
void DLL::pop(const elem_pos where)
{
    if (head != nullptr && tail != nullptr)
    {
        //special case - one element
        if (head == tail)
        {
           tail = nullptr;
           delete head;
           elcount = 0;
           head = nullptr;
        }
        else
        {
            if (where == FRONT)
            {
                Node * cleaner = head;
                head = head->next;
                //breaking bonds
                head->prev = nullptr;
                cleaner->next = nullptr;

                delete cleaner;
                --elcount;
                cleaner = nullptr;
            }
            else if (where == MID)
            {
                if (elcount == 2) pop(DLL::FRONT);
                else
                {
                    int count = 1;
                    int limit = elcount / 2;
                    limit = (elcount % 2 == 0)? limit : (limit + 1);

                    Node * temp = head;
                    while (count != limit)
                    {
                        temp = temp->next;
                        ++count;
                    }
                    temp->next->prev = temp->prev;
                    temp->prev->next = temp->next;
                    temp->prev = nullptr;
                    temp->next = nullptr;
                    delete temp;
                    --elcount;
                    temp = nullptr;
                }
            }
            else if (where == BACK)
            {
                Node * cleaner = tail;
                tail = tail->prev;
                //breaking bonds
                tail->next = nullptr;
                cleaner->prev = nullptr;

                delete cleaner;
                --elcount;
                cleaner = nullptr;
            }
        }
    }
}

/*
 * inserts element in custom position,
 * AFTER 'pos' parameter. Possible range is [0..list.size],
 * but it contains 'out of border' check as well.
 *
 * note: pushing in '0' position is interpreted as pushing FRONT.
 */
void DLL::insert(const int pos, const int element)
{
    if (pos < 0) return;

    if (pos == 0) push(DLL::FRONT, element);
    else if (is_mid(pos)) push(DLL::MID, element);
    else if (pos >= elcount || head == tail) push(DLL::BACK, element);
    else
    {
        Node * temp = nullptr;

        if (closer_to_head(pos))
        {
            temp = head;
            int count = 1;
            while (count != pos)
            {
                temp = temp->next;
                ++count;
            }
        }
        else if (closer_to_tail(pos))
        {
            /*
             * no need to start from tail, as we're
             * moving back, the trivial case is
             * insertion element before tail
             */
            temp = tail->prev;
            int count = elcount - 1;
            while (count != pos)
            {
                temp = temp->prev;
                --count;
            }
        }

        Node * alloc = new Node(element);
        ++elcount;
        temp->next->prev = alloc;
        alloc->prev = temp;
        alloc->next = temp->next;
        temp->next = alloc;
        alloc = temp = nullptr;
    }


}

/*
 * removes element at exact 'pos' position.
 * Possible range is [1..list.size].
 *
 * Putting value greater than list.size is interpreted as
 * popping from BACK.
 *
 * Won't work if there's nothing to remove.
 */
void DLL::remove(const int pos)
{
    if (pos < 1 || (head == nullptr && tail == nullptr)) return;

    if (pos == 1) pop(DLL::FRONT);
    else if (is_mid(pos)) pop(DLL::MID);
    else if (pos >= elcount) pop(DLL::BACK);
    else
    {
        Node * temp = nullptr;

        if (closer_to_head(pos))
        {
            /*
             * no need to start from head, as this case,
             * is handled above. Yeah, might be confusing,
             * if comparing to 'insert' method, but
             * previously we inserted AFTER 'pos'.
             */
            temp = head->next;
            int count = 2;
            while (count != pos)
            {
                temp = temp->next;
                ++count;
            }
        }
        else if (closer_to_tail(pos))
        {
            /*
             * again, trivial case -
             * removing element before tail
             */
            temp = tail->prev;
            int count = elcount - 1;
            while (count != pos)
            {
                temp = temp->prev;
                --count;
            }
        }

        temp->next->prev = temp->prev;
        temp->prev->next = temp->next;
        temp->next = nullptr;
        temp->prev = nullptr;
        delete temp;
        --elcount;
        temp = nullptr;
    }

}

void DLL::merge(const DLL & obj)
{
    if (elcount == 0) *this = obj;
    else
    {
        if (obj.elcount != 0)
        {
            DLL add(obj);
            elcount += add.elcount;
            tail->next = add.head;
            add.head->prev = tail;
            tail = add.tail;
            add.head = add.tail = nullptr;
        }
    }
}

void DLL::sort(const type_sort which)
{
    if (elcount < 2) return;

    int * ar = new int[elcount];

    for (int i = 1 ; i <= elcount; i++) ar[i - 1] = at(i);

    if (which == QUICK) quick_sort(ar, elcount);
    else if (which == BUBBLE) bubble_sort(ar, elcount);
    else if (which == SELECT) select_sort(ar, elcount);
    else if (which == INSERT) insert_sort(ar, elcount);

    for (int i = 1; i <= elcount; i++) refresh(i, ar[i - 1]);

    delete [] ar;
}

void DLL::clear()
{
    tail = nullptr;
    elcount = 0;
    Node * cleaner;
    while (head != nullptr)
    {
        cleaner = head;
        head = head->next;
        delete cleaner;
    }
    cleaner = nullptr;
}

void DLL::reverse()
{
    if (head == tail) return;

    Node * temp = tail;
    tail->next = tail->prev;
    tail->prev->next = nullptr; //temporary
    Node * temp_head = temp;
    temp = tail->next;
    tail->prev = nullptr;

    while (temp != head)
    {
        temp->prev->next = nullptr; //temporay;
        temp->next = temp->prev;
        temp->prev = temp_head;
        temp_head = temp;
        temp = temp->next;
    }
    /*
     * now we reached the original head,
     * where temp (a.k.a head) will soon
     * become tail
     */
    temp->prev = temp_head;
    temp->next = nullptr;
    //get rid of temps;
    temp_head = temp = nullptr;

    //now change: head->tail, tail->head
    Node * change = head;
    head = tail;
    tail = change;
    change = nullptr;
}

void DLL::resize(const int newsize)
{
    if (newsize < 0 || newsize == elcount) return;

    if (newsize < elcount) while (elcount != newsize) pop(BACK);
    else while (elcount != newsize) push(BACK, 0);
}

/*
 * replaces old value at given position with a new one,
 * allocates memory if needed
 */
void DLL::refresh(const int pos, const int newvalue)
{
    if (pos < 1) return;

    if (pos > elcount) push(BACK, newvalue);
    else
    {
        if (closer_to_head(pos) || is_mid(pos))
        {
            Node * runner = head;
            int count = 1;
            while (count != pos)
            {
                runner = runner->next;
                ++count;
            }
            runner->data = newvalue;
        }
        else if (closer_to_tail(pos))
        {
            Node * runner = tail;
            int count = elcount;
            while (count != pos)
            {
                runner = runner->prev;
                --count;
            }
            runner->data = newvalue;
        }
    }

}

//non-modifying methods

/*
 * consider we have the following list:
 * 1->2->3->4->5
 *
 * calling this function with 'pos1' and 'pos2' parameters,
 * e.g. '2' and '4' and 'WHITELIST' parameter gives us:
 * 2->3->4
 *
 * when using 'BLACKLIST' parameter, the result is:
 * 1->5
 *
 * Possible range : [1..list.size].
 *
 * Extra cases when using WHITELIST mode:
 * - equality of 'pos1' and 'pos2' is acceptable and returns
 * list with one element
 * - passing 'pos1' > 'pos2' returns reverse-ordered slice
 */
DLL DLL::slice(const int pos1, const int pos2,
               const slicetype which) const
{
    DLL result;

    if (pos1 < 1 || pos1 > elcount
     || pos2 < 1 || pos2 > elcount
     || elcount == 0) return result;

    if (which == WHITELIST)
    {
        if (pos1 == pos2)
        {
            if (pos1 == 1) result.push(BACK, head->data);
            else if (pos1 == elcount) result.push(BACK, tail->data);
            else
            {
                Node * temp = nullptr;
                int count = 0;

                if (closer_to_head(pos1) || is_mid(pos1))
                {
                    temp = head->next;
                    count = 2;
                    while (count != pos1)
                    {
                        temp = temp->next;
                        ++count;
                    }
                }
                else if (closer_to_tail(pos1))
                {
                    temp = tail->prev;
                    count = elcount - 1;
                    while (count != pos1)
                    {
                        temp = temp->prev;
                        --count;
                    }
                }
                result.push(BACK, temp->data);
            }
        }
        else
        {
            if (pos1 < pos2)
            {
                /*
                 * if the first pos is closer to head - it matters not, whether
                 * the second position is closer to head, or tail
                 * as we have direct order
                 */

                if (closer_to_head(pos1))
                {
                    Node * runner = head;
                    int count = 1;
                    while (count != pos2 + 1)
                    {
                        if (count >= pos1) result.push(BACK, runner->data);
                        runner = runner->next;
                        ++count;
                    }
                    runner = nullptr;
                }
                else
                {
                    /*
                     * otherwise we start our journey from tail,
                     * then just reverse order with 'reverse' method
                    */
                    Node * runner = tail;
                    int count = elcount;
                    while (count != pos1 - 1)
                    {
                        if (count <= pos2) result.push(BACK, runner->data);
                        runner = runner->prev;
                        --count;
                    }
                    runner = nullptr;
                    result.reverse();
                }

            }
            else
            {
                /*
                 * again, check if first pos is closer to tail,
                 * if so - second pos doesn't matter, as
                 * going back from tail when pos1 > pos2 is simple
                 * 'direct' order.
                 */
                if (closer_to_tail(pos1))
                {
                    Node * runner = tail;
                    int count = elcount;
                    while (count != pos2 - 1)
                    {
                        if (count <= pos1) result.push(BACK, runner->data);
                        runner = runner->prev;
                        --count;
                    }
                    runner = nullptr;
                }
                else
                {
                    /*
                     * otherwise we start from head, and then
                     * reverse order
                     */
                    Node * runner = head;
                    int count = 1;
                    while (count != pos1 + 1)
                    {
                        if (count >= pos2) result.push(BACK, runner->data);
                        runner = runner->next;
                        ++count;
                    }
                    runner = nullptr;
                    result.reverse();
                }
            }
        }
    }
    else if (which == BLACKLIST)
    {
        //in BLACKLIST mode the order doesn't matter
        int pos1_fix = (pos1 < pos2)? pos1 : pos2;
        int pos2_fix = (pos1 < pos2)? pos2 : pos1;

        if (pos1_fix == pos2_fix
        || (pos1_fix == 1 && pos2_fix == elcount)
           ) return result;
        else
        {
            if (pos1_fix == 1 && pos2_fix != elcount)
            {
                Node * runner = tail;
                int count = elcount;

                while (count != pos2_fix)
                {
                    result.push(BACK, runner->data);
                    runner = runner->prev;
                    --count;
                }
                result.reverse();
            }
            else if (pos1_fix != 1 && pos2_fix == elcount)
            {
                Node * runner = head;
                int count = 1;

                while (count != pos1_fix)
                {
                    result.push(BACK, runner->data);
                    runner = runner->next;
                    ++count;
                }
            }
            else
            {
                Node * runner = head;
                int count = 1;
                while (count <= elcount)
                {
                    if (count < pos1_fix
                     || count > pos2_fix) result.push(BACK, runner->data);
                    runner = runner->next;
                    ++count;
                }
            }

        }
    }

    return result;
}

/*
 * returns a copy of element at given 'pos' parameter,
 * returns trash if 'pos' is out of list's range.
*/
int DLL::at(const int pos) const
{
    int result;

    if (pos < 1 || pos > elcount || elcount == 0) return std::sqrt(-1);

    if (closer_to_head(pos) || is_mid(pos))
    {
        Node * runner = head;
        int count = 1;
        while (count != pos)
        {
            runner = runner->next;
            ++count;
        }
        result = runner->data;
        runner = nullptr;
    }
    else if (closer_to_tail(pos))
    {
        Node * runner = tail;
        int count = elcount;
        while (count != pos)
        {
            runner = runner->prev;
            --count;
        }
        result = runner->data;
        runner = nullptr;
    }

    return result;
}

void DLL::print() const
{
    if (head != nullptr && tail != nullptr)
    {
        std::cout << head->data << std::endl;

        Node * temp = head->next;

        while (temp != nullptr)
        {
            std::cout << temp->data << std::endl;
            temp = temp->next;
        }
    }
}



//
