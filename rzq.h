#ifndef __RZQ_H__
#define __RZQ_H__

namespace rzq
{
    template <typename ty>
    class lb
    { // 链表
    protected:
        header_alb *head = nullptr;

    public:
        struct alb
        { // 链表基本部分
            ty info;
            alb *next = nullptr;
            alb *last = nullptr;
        };

        struct header_alb
        { // 头链表，记录链表长度（不包含头链表）
            int len = 1;
            alb *begin = nullptr;
            alb *end = nullptr;
        };

        lb()
        {
            this->head = new header_alb; // 指向头链表的指针
            head->begin = new alb;
            head->end = head->begin;
            (head->begin)->next = head->begin;
            (head->begin)->last = head->begin;
        }

        auto length() -> int
        { // 计算长度
            return (this->head)->len;
        }

        void insert(int i, ty infomation)
        {
            alb *p = this->at(i); // 在即将插入的部分之后的部分
            alb *q = p->last;     // 在即将插入的部分之前的部分
            alb *n = new alb;
            n->info = infomation;
            n->next = p;
            n->last = q;
            q->next = n;
            p->last = n;
            ((this->head)->len)++;
        }

        auto at(int i) -> alb *
        {
            alb *b = nullptr;
            if (i == 0)
            {
                throw "没有零索引！";
            }
            if (i > 0)
            {
                i = i % ((this->head)->len);
                int a = 1;
                b = (this->head)->begin;
                while (a <= i)
                {
                    b = b->next;
                    a++;
                }
            }
            else
            {
                i = (0 - i) % ((this->head)->len);
                int a = 1;
                b = (this->head)->end;
                while (a <= i)
                {
                    b = b->last;
                    a++;
                }
            }

            return b;
        }

        // 以下由AI自动生成
        // 说起来，AI挺喜欢用我前面写的一些基础函数呢，哈哈哈哈
        // 不过，AI写的代码有些也有问题，例如我写的这个lb类没有零索引，AI容易忘记

        ty &operator[](int i) // 重载[]运算符
        {
            return (this->at(i))->info;
        }

        void remove(int i)
        {
            alb *p = this->at(i);
            alb *q = p->last;
            alb *r = p->next;
            q->next = r;
            r->last = q;
            delete p;
            ((this->head)->len)--;
        }

        void clear() // 清空链表
        {
            alb *p = (this->head)->begin->next;
            while (p != (this->head)->end) // 最后一个元素没删除
            {
                alb *q = p->next;
                delete p;
                p = q;
            }
            delete p; // 最后一个元素删除
            p = nullptr;
            (this->head)->len = 1;
            (this->head)->begin->next = (this->head)->begin;
            (this->head)->begin->last = (this->head)->begin;
            (this->head)->end = (this->head)->begin;
        }

        void push_back(ty infomation) // 尾部插入
        {
            insert((this->head)->len + 1, infomation);
        }

        void pop_back() // 尾部删除
        {
            remove((this->head)->len);
        }

        void push_front(ty infomation) // 头部插入
        {
            insert(1, infomation);
        }

        void pop_front() // 头部删除
        {
            remove(1);
        }

        auto begin() -> alb *
        {
            return (this->head)->begin;
        }

        auto end() -> alb *
        {
            return (this->head)->end;
        }
    };

}
#endif
