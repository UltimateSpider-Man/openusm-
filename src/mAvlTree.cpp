#include "mAvlTree.h"

#include "common.h"
#include "mash_info_struct.h"
#include "utility.h"

VALIDATE_SIZE(mAvlTree<string_hash_entry>, 16u);

template<>
void mAvlTree<string_hash_entry>::sub_564370(mAvlNode<string_hash_entry> **a1) {
    auto v2 = a1;
    auto v3 = *a1;
    auto v4 = (*a1)->m_left;
    auto a1a = (*a1)->m_parent;
    v3->m_left = v4->m_right;
    auto v5 = (*v2)->m_left;
    if (v5) {
        v5->m_parent = *v2;
    }

    auto v6 = *v2;
    auto v7 = (*v2 == nullptr);
    v4->m_right = *v2;
    if (!v7) {
        v6->m_parent = v4;
    }

    auto v8 = *v2;
    auto *v9 = (*v2)->m_left;
    char v10 = -1;
    if (v9) {
        v10 = v9->field_10;
    }

    auto *v11 = v8->m_right;
    char v12 = -1;
    if (v11) {
        v12 = v11->field_10;
    }

    char v13;
    [&]() {
        if (v10 <= v12) {
            if (v11) {
                v13 = v11->field_10;
                return;
            }
        } else if (v9) {
            v13 = v9->field_10;
            return;
        }
        v13 = -1;
    }();

    v8->field_10 = v13 + 1;
    auto *v14 = v4->m_left;
    char v15 = -1;
    if (v14) {
        v15 = v14->field_10;
    }

    auto v16 = (*v2)->field_10;
    if (v15 > v16) {
        if (v14) {
            v4->field_10 = v14->field_10 + 1;
            *v2 = v4;
            v4->m_parent = a1a;
            return;
        }
        v16 = -1;
    }
    v4->field_10 = v16 + 1;
    *v2 = v4;
    v4->m_parent = a1a;
}

template<>
void mAvlTree<string_hash_entry>::sub_43BF70(mAvlNode<string_hash_entry> **a1) {
    auto v2 = a1;
    auto v3 = *a1;
    auto v4 = (*a1)->m_right;
    auto a1a = (*a1)->m_parent;
    v3->m_right = v4->m_left;
    auto *v5 = v4->m_left;
    if (v5) {
        v5->m_parent = *v2;
    }

    v4->m_left = *v2;
    if (*v2) {
        (*v2)->m_parent = v4;
    }

    auto v6 = *v2;
    auto v7 = (*v2)->m_left;
    char v8 = -1;
    if (v7) {
        v8 = v7->field_10;
    }

    auto *v9 = v6->m_right;
    char v10 = -1;
    if (v9) {
        v10 = v9->field_10;
    }

    char v11;
    [&]() {
        if (v8 <= v10) {
            if (v9) {
                v11 = v9->field_10;
                return;
            }
        } else if (v7) {
            v11 = v7->field_10;
            return;
        }

        v11 = -1;
    }();

    v6->field_10 = v11 + 1;
    auto *v12 = v4->m_right;
    char v13 = -1;
    if (v12) {
        v13 = v12->field_10;
    }

    auto v14 = (*v2)->field_10;
    if (v13 > v14) {
        if (v12) {
            v4->field_10 = v12->field_10 + 1;
            *v2 = v4;
            v4->m_parent = a1a;
            return;
        }
        v14 = -1;
    }

    v4->field_10 = v14 + 1;
    *v2 = v4;
    v4->m_parent = a1a;
}

template<>
void mAvlTree<string_hash_entry>::sub_744960(mAvlNode<string_hash_entry> **a1) {
    this->sub_564370(&(*a1)->m_right);
    this->sub_43BF70(a1);
}

template<>
void mAvlTree<string_hash_entry>::sub_745DF0(mAvlNode<string_hash_entry> **a2) {
    this->sub_43BF70(&(*a2)->m_left);
    this->sub_564370(a2);
}

template<>
int *mAvlTree<string_hash_entry>::sub_64A090(int *a2) {
    return (int *) THISCALL(0x0064A090, this, a2);
}

template<>
void mAvlTree<string_hash_entry>::sub_64A2B0() {
    THISCALL(0x0064A2B0, this);
}

template<>
void mAvlTree<string_hash_entry>::sub_439AD0(mAvlNode<string_hash_entry> *a1) {
    auto *v2 = a1->m_left;
    char v3 = -1;
    if (v2 != nullptr) {
        v3 = v2->field_10;
    }

    auto *v4 = a1->m_right;
    char v5 = -1;
    if (v4 != nullptr) {
        v5 = v4->field_10;
    }

    if (v3 <= v5) {
        if (v4) {
            a1->field_10 = v4->field_10 + 1;
            return;
        }

    } else if (v2) {
        a1->field_10 = v2->field_10 + 1;
        return;
    }

    a1->field_10 = 0;
}

int sub_561350(mAvlNode<string_hash_entry> *a1, mAvlNode<string_hash_entry> *a2) {
    int result = -1;

    auto v2 = a2->m_key->field_0.source_hash_code;
    auto v3 = a1->m_key->field_0.source_hash_code;
    if (v3 <= v2) {
        result = -(v3 < v2);
    }

    return result;
}

//0x0056AE30
template<>
int mAvlTree<string_hash_entry>::addHelper(mAvlNode<string_hash_entry> *a2,
                                           mAvlNode<string_hash_entry> *&a3,
                                           mAvlNode<string_hash_entry> *a4) {
    if constexpr (1) {
        int result;
        auto v4 = a3;
        auto &v5 = *a3;

        if (a3 != nullptr) {
            auto v8 = v5.m_key->field_0.source_hash_code;
            auto v9 = a2;
            auto v10 = a2->m_key->field_0.source_hash_code;
            if (v10 > v8) {
                auto a2b = this->addHelper(a2, v5.m_right, &v5);
                auto v16 = *a3;
                auto v17 = a3->m_right;
                char a1a = -1;
                if (v17) {
                    a1a = v17->field_10;
                }

                char v19 = -1;
                auto v18 = v16.m_left;
                if (v18) {
                    v19 = v18->field_10;
                }

                if (a1a - v19 == 2) {
                    if (sub_561350(v9, v17) <= 0) {
                        this->sub_744960(&v4);
                    } else {
                        this->sub_43BF70(&v4);
                    }

                    result = a2b;
                } else {
                    this->sub_439AD0(&v16);
                    result = a2b;
                }

            } else if (v10 < v8) {
                auto v11 = this->addHelper(a2, v5.m_left, &v5);
                auto v12 = *a3;
                auto a2a = v11;
                auto *v13 = (*a3).m_left;
                char a1 = -1;
                if (v13) {
                    a1 = v13->field_10;
                }

                auto *v14 = v12.m_right;
                char v15 = -1;
                if (v14) {
                    v15 = v14->field_10;
                }

                if ((char) a1 - v15 == 2) {
                    if (v9->m_key->field_0.source_hash_code >=
                        v13->m_key->field_0.source_hash_code) {
                        this->sub_745DF0(&v4);
                    } else {
                        this->sub_564370(&v4);
                    }

                    result = a2a;
                } else {
                    this->sub_439AD0(&v12);
                    result = a2a;
                }
            } else {
                result = 0;
            }
        } else {
            a2->m_parent = a4;
            a3 = a2;
            ++this->m_size;
            result = 1;
        }
        return result;
    } else {
        return THISCALL(0x0056AE30, this, a2, a3, a4);
    }
}

template<>
void mAvlTree<string_hash_entry>::unmash(mash_info_struct *a2, [[maybe_unused]] void *a3) {
    if constexpr (1)
    {
        auto size = this->m_size;
        auto **v5 = &this->m_head;
        auto *v6 = a2;
        this->m_head = nullptr;
        this->m_size = 0;
        if (size > 0) {
            auto i = size;
            do {
                auto *v7 = (mAvlNode<string_hash_entry> *)
                               v6->read_from_buffer(
#ifdef TARGET_XBOX
                                       mash::NORMAL_BUFFER,
#endif 
                                       sizeof(mAvlNode<string_hash_entry>), 4);
                if (v7->m_key != nullptr) {
                    auto *v8 = (string_hash_entry *) v6->read_from_buffer(
#ifdef TARGET_XBOX
                        mash::NORMAL_BUFFER,
#endif
                            sizeof(string_hash_entry), 4);

                    v7->m_key = v8;
                    v6->unmash_class_in_place(v8->field_4, v8);
                }

                this->addHelper(v7, *v5, nullptr);
                --i;
            } while (i);
        }

        this->field_0 = (int) &v6->mash_image_ptr[v6->buffer_size_used[0] - (DWORD) this];
    }
    else {
        THISCALL(0x00570900, this, a2, a3);
    }
}

void mAvlTree_patch() {
    {
        FUNC_ADDRESS(address, &mAvlTree<string_hash_entry>::findHelper);
        REDIRECT(0x00531A07, address);
    }

    {
        FUNC_ADDRESS(address, &mAvlTree<string_hash_entry>::iterator::iterate);
        //REDIRECT(0x0052A7C2, address);
    }

    {
        FUNC_ADDRESS(address, &mAvlTree<string_hash_entry>::unmash);
        REDIRECT(0x00550F44, address);
    }
}
