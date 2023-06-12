#include <stdio.h>
#include <stdlib.h>

struct Elm {
        int x;
        int height;
        int len;
        struct Elm *L;
        struct Elm *R;
};
typedef struct Elm Elm;

// Binary Search Tree
struct BST {
        Elm *root;
};
typedef struct BST BST;

void bs_put(BST *, int);
Elm *bs_get(const BST *, int);
void bs_del(BST *, int);
int bs_delMin(BST *);
void bs_inorder(const BST *);
int bs_rank(const BST *, int);
int bs_size(const BST *, int);
Elm *bs_floor(const BST *, int);
Elm *bs_ceiling(const BST *, int);
int bs_height(const BST *, int);

Elm *create(int x)
{
        Elm *el = (struct Elm *)malloc(sizeof(Elm));
        el->x = x;
        el->height = 1;
        el->len = 1;
        el->L = NULL;
        el->R = NULL;
        return el;
}

void insert(Elm *root, int x)
{
        if (root->x > x)
        {
                // зүүн
                // printf("\nleft\n");
                if (root->L == NULL)
                {
                        root->L = create(x);
                }
                else
                {
                        insert(root->L, x);
                }
        }
        else
        {
                // баруун
                // printf("\right\n");
                if (root->R == NULL)
                {
                        root->R = create(x);
                }
                else
                {
                        insert(root->R, x);
                }
        }
        // хэрвээ хүүхэдтэй бол аль их өндөртэй дээр нь нэгийг нэмнэ
        if (root->L && root->R)
        {
                if (root->L->height > root->R->height)
                {
                        root->height = root->L->height + 1;
                }
                else
                {
                        root->height = root->R->height + 1;
                }
        }
        else if (root->L)
        {
                root->height = root->L->height + 1;
        }
        else if (root->R)
        {
                root->height = root->R->height + 1;
        }
        else
        {
                root->height++;
        }
        root->len++;
}

void bs_put(BST *ptree, int x)
{
        if (ptree->root == NULL)
        {
                ptree->root = create(x);
                return;
        }
        insert(ptree->root, x);
        // printf(" %d", ptree->root->x);
}

/*
  `ptree`-ийн зааж байгаа модноос `x` утгыг хайн олдсон оройн `Elm*` хаягийг буцаана.
  Олдохгүй бол `NULL` хаягийг буцаана.
  Мод дандаа ялгаатай элементүүд хадгална гэж үзэж болно.
 */
Elm *search(Elm *root, int x)
{
        if (root == NULL)
        {
                return NULL;
        }
        if (root->x == x)
        {
                // printf("\nreturning: %d", root->x);
                return root;
        }
        if (root->x > x)
        {
                // printf("\nleft: %d\n", root->x);
                return search(root->L, x);
        }
        else
        {
                // printf("\nright: %d\n", root->x);
                return search(root->R, x);
        }
}

Elm *bs_get(const BST *ptree, int x)
{
        // Мод хоосон
        if (ptree->root == NULL)
        {
                // printf("Root is null");
                return NULL;
        }
        // Мод хоосон биш
        return search(ptree->root, x);
}

/*
  Устгах функц: ХХМноос `x` утгыг хайж олоод устгана.
  Олдохгүй бол юу ч хийхгүй.
 */
Elm *rightMinValue(Elm *root)
{
        Elm *tmp = root;
        while (tmp && tmp->L != NULL)
        {
                tmp = tmp->L;
        }
        return tmp;
}

Elm *del(Elm *root, int x)
{
        if (root == NULL)
        {
                printf("\nRoot null\n");
                return NULL;
        }
        if (root->x == x)
        {
                printf("\nFound\n");
                if (root->L == NULL && root->R == NULL)
                { // Навч байвал
                        printf("\nFound and leaf");
                        free(root);
                        return NULL;
                }
                else if (root->R == NULL)
                { // Ганц хүү байвал
                        printf("\nFound and left");
                        Elm *tmp = root->L;
                        free(root);
                        return tmp;
                }
                else if (root->L == NULL)
                { // Ганц хүү байвал
                        printf("\nFound and right");
                        Elm *tmp = root->R;
                        free(root);
                        return tmp;
                }
                else
                { // Хоёр хүү байвал
                        printf("\nFound and both child");
                        Elm *tmp = rightMinValue(root->R);
                        root->x = tmp->x;
                        root->R = del(root->R, tmp->x);
                        return root;
                }
        }
        // Зүүн
        else if (root->x > x)
        {
                printf("\nLeft\n");
                root->L = del(root->L, x);
        }
        else // Баруун
        {
                printf("\nRight\n");
                root->R = del(root->R, x);
        }

        // 2 хүү байвал
        if (root->L && root->R)
        {
                if (root->L->height > root->R->height)
                {
                        root->height = root->L->height + 1;
                }
                else
                {
                        root->height = root->R->height + 1;
                }
        }
        else if (root->L && root->R == NULL)
        { // Ганц хүү байвал
                root->height = root->L->height + 1;
        }
        else if (root->R && root->L == NULL)
        { // ганц хүү байвал
                root->height = root->L->height + 1;
        }
        else // Хүүгүй бол
        {
                printf("huugui");
                root->height--;
        }
        root->len--;
    return root;
}

void bs_del(BST *ptree, int x)
{
        // Мод хоосон
        if (ptree->root == NULL)
        {
                return;
        }
        // Мод хоосон биш
        del(ptree->root, x);
}

/*
  Хамгийн багыг устгах функц: ХХМноос хамгийг бага утгыг нь устгах функц.
  Устгасан утгыг буцаана.
 */
int bs_delMin(BST *ptree)
{
    return 1;  // Функцийг хэрэгжүүлнэ үү
}

/*
  ХХМыг inorder дарааллаар, нэг мөрөнд нэг утга хэвлэнэ.
 */
void bs_inorder(const BST *ptree)
{
        // Функцийг хэрэгжүүлнэ үү
    return;
}

/*
  ХХМноос `x` утгаас эрс бага буюу тэнцүү байх хэдэн орой байгааг олж буцаана.
  Өөрөөр хэлбэл хоёртын хайлтын модны утгуудыг өсөх дарааллаар байрлуулбал
  `x`-ийг оролцуулаад өмнө хэдэн тоо байх вэ? гэсэн үг.
  `x` утга заавал модонд байх албагүй.
 */
int bs_rank(const BST *ptree, int x)
{
        // Функцийг хэрэгжүүлнэ үү
    return 1;
}

/*
  ХХМноос `x` утгатай оройг хайж олоод, тухайн оройд суурилсан
  дэд модонд хэдэн орой байгааг олж буцаана.
  Олдохгүй бол -1-ийг буцаана.
 */
int bs_size(const BST *ptree, int x)
{
        // Функцийг хэрэгжүүлнэ үү
    return 1;
}

/*
  XXMноос `x`-ээс бага буюу тэнцүү байх хамгийн их утгын `Elm *` хаягийг олж буцаана.
  Олдохгүй бол `NULL` хаягийг буцаана.
 */
Elm *bs_floor(const BST *ptree, int x)
{
        // Функцийг хэрэгжүүлнэ үү
    return NULL;
}

/*
  XXMноос `x`-ээс их буюу тэнцүү байх хамгийн бага утгын `Elm *` хаягийг олж буцаана.
  Олдохгүй бол `NULL` хаягийг буцаана.
 */
Elm *bs_ceiling(const BST *ptree, int x)
{
        // Функцийг хэрэгжүүлнэ үү
    return NULL;
}

/*
  ХХМноос `x` утгатай оройг хайж олоод, тухайн оройд суурилсан
  дэд модны өндөр хэд байгааг олж буцаана. Олдохгүй бол -1-ийг буцаана.
 */
int bs_height(const BST *ptree, int x)
{
        // Функцийг хэрэгжүүлнэ үү
    return 1;
}

int main()
{
        int x, t, y;
        BST bst;
        bst.root = NULL;
        Elm *p;
        
        while (1) {
                printf("1: put, 2: get, 3: del, 4: delMin, 5: inorder, "
                       "6: rank, 7: size, 8: floor, 9: ceiling, 10: height, 11: exit\n");
                scanf("%d", &t);

                switch (t) {
                case 1:
                        printf("Oruulax utga: ");
                        scanf("%d", &x);
                        bs_put(&bst, x);
                        break;
                case 2:
                        printf("Xandax utga: ");
                        scanf("%d", &x);
                        p = bs_get(&bst, x);
                        if (p == NULL)
                                printf("Oldsongui\n");
                        else {
                                printf("Utga: %d\n", p->x);
                                printf("len: %d\n", p->len);
                                printf("height: %d\n", p->height);
                        }
                        break;
                case 3:
                        printf("Ustgax utga: ");
                        scanf("%d", &x);
                        bs_del(&bst, x);
                        break;
                case 4:
                        if (bst.root) {
                                x = bs_delMin(&bst);
                                printf("Ustgasan xamgiin baga utga: %d\n", x);
                        } else
                                printf("Mod xooson\n");
                        break;
                case 5:
                        bs_inorder(&bst);
                        break;
                case 6:
                        printf("Rank olox utga: ");
                        scanf("%d", &x);
                        y = bs_rank(&bst, x);
                        printf("Rank(%d): %d\n", x, y);
                        break;
                case 7:
                        printf("Xemjee olox utga: ");
                        scanf("%d", &x);
                        y = bs_size(&bst, x);
                        printf("Size(%d): %d\n", x, y);
                        break;
                case 8:
                        printf("Dood buxel olox utga: ");
                        scanf("%d", &x);
                        p = bs_floor(&bst, x);
                        if (p != NULL)
                                printf("Floor(%d): %d\n", x, p->x);
                        else
                                printf("odlsongui\n");
                        break;
                case 9:
                        printf("Deed buxel olox utga: ");
                        scanf("%d", &x);
                        p = bs_ceiling(&bst, x);
                        if (p != NULL)
                                printf("Ceiling(%d): %d\n", x, p->x);
                        else
                                printf("odlsongui\n");
                        break;
                case 10:
                        printf("Undur olox utga: ");
                        scanf("%d", &x);
                        y = bs_height(&bst, x);
                        printf("Height(%d): %d\n", x, y);
                        break;
                case 11:
                        exit(0);
                default:
                        break;
                }
        }
        return 0;
}
