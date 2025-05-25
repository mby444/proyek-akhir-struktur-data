#include <iostream>
#include <string>
#include <cstdint>
#include <cctype>

using namespace std;

#define MAX_ARTICLE 100
#define MAX_COMMENT 100
#define MAX_ADJ 10
#define MAX_HISTORY 50

void outputMainHeader()
{
    cout << "======================================" << endl;
    cout << "         DATA STRUKTUR EXPLORER       " << endl;
    cout << "     Sistem Mini-Ensklopedia Interaktif" << endl;
    cout << "======================================" << endl;
    cout << "1. Masuk Sebagai Pengunjung" << endl;
    cout << "2. Masuk Sebagai Editor" << endl;
    cout << "0. Keluar" << endl;
    cout << endl;
}

void outputHeaderEditor()
{
    cout << "======================================" << endl;
    cout << "         DATA STRUKTUR EXPLORER       " << endl;
    cout << "     Sistem Mini-Ensklopedia Interaktif" << endl;
    cout << "======================================" << endl;
    cout << "                -- Editor --" << endl;
    cout << "1. Lihat Semua Artikel" << endl;
    cout << "2. Tambah Artikel" << endl;
    cout << "3. Cari dan Edit Artikel" << endl;
    cout << "4. Lihat Tampilan Terurut" << endl;
    cout << "5. Komentar Masuk" << endl;
    cout << "0. Kembali" << endl;
    cout << endl;
}

void outputHeaderVisitor()
{
    cout << "======================================" << endl;
    cout << "         DATA STRUKTUR EXPLORER       " << endl;
    cout << "     Sistem Mini-Ensklopedia Interaktif" << endl;
    cout << "======================================" << endl;
    cout << "              -- Pengunjung --" << endl;
    cout << "1. Lihat Semua Artikel" << endl;
    cout << "2. Lihat Tampilan Terurut" << endl;
    cout << "3. Cari dan Baca Artikel" << endl;
    cout << "4. Tambahkan Komentar" << endl;
    cout << "5. Lihat Riwayat Bacaan" << endl;
    cout << "6. Jelajahi Topik Terkait" << endl;
    cout << "7. Jelajahi Kategori Artikel" << endl;
    cout << "0. Keluar" << endl;
    cout << endl;
}

string inputData(string label)
{
    cout << label << "> ";
    string data;
    getline(cin, data);

    while (data.empty())
    {
        cout << "Input tidak boleh kosong. " << label << "> ";
        getline(cin, data);
    }

    return data;
}

char inputChar(string label)
{
    char ch;
    cout << label << "> ";
    cin >> ch;

    while (cin.fail())
    {
        cin.clear();
        cin.ignore(1000, '\n');
        cout << "Input tidak valid. Harap masukkan karakter yang sesuai." << endl;
        cout << label << "> ";
        cin >> ch;
    }

    cin.ignore(1000, '\n');
    return ch;
}

int inputMenu()
{
    int choice;
    while (true)
    {
        cout << "Pilih menu> ";
        cin >> choice;
        if (cin.fail())
        {
            cin.clear();
            cin.ignore(1000, '\n');
            cout << "Input tidak valid. Masukkan angka yang sesuai menu." << endl;
        }
        else
        {
            cin.ignore(1000, '\n');
            return choice;
        }
    }
}

bool inputYN(string label)
{
    string answer;
    while (true)
    {
        cout << label << " (Y/N): ";
        cin >> answer;

        if (answer == "Y" || answer == "y")
            return true;
        if (answer == "N" || answer == "n")
            return false;

        cout << "Input tidak valid. Harap masukkan Y atau N." << endl;
        cin.ignore(1000, '\n');
    }
}

int inputInteger(string label)
{
    int value;
    cout << label << "> ";
    cin >> value;

    while (cin.fail() || value < 0)
    {
        cin.clear();
        cin.ignore(1000, '\n');
        cout << "Input tidak valid. Masukkan angka positif." << endl;
        cout << label << "> ";
        cin >> value;
    }

    cin.ignore(1000, '\n');

    return value;
}

bool isValidArticleIdFormat(const string &id)
{
    if (id.length() != 4)
        return false;

    if (id[0] != 'A')
        return false;

    for (int i = 1; i < 4; ++i)
    {
        if (!isdigit(id[i]))
            return false;
    }

    return true;
}

string inputId(const string &label)
{
    string id;
    while (true)
    {
        cout << label << "> ";
        getline(cin, id);

        if (!isValidArticleIdFormat(id))
        {
            cout << "Format ID tidak valid. Gunakan format A### (contoh: A001)." << endl;
            continue;
        }

        return id;
    }
}

bool isArticleId(const string &str)
{
    if (str.length() != 4)
        return false;

    if (str[0] != 'A')
        return false;

    for (int i = 1; i < 4; ++i)
    {
        if (!isdigit(str[i]))
            return false;
    }

    return true;
}

struct CommentNode
{
    string articleId;
    string text;
    CommentNode *next;

    CommentNode(string id, string txt) : articleId(id), text(txt), next(nullptr) {}
};

struct CommentQueue
{
    CommentNode *frontComment = nullptr;
    CommentNode *rearComment = nullptr;

    void enqueueComment(string articleId, string text)
    {
        CommentNode *newNode = new CommentNode(articleId, text);

        if (rearComment == nullptr)
        {
            frontComment = rearComment = newNode;
        }
        else
        {
            rearComment->next = newNode;
            rearComment = newNode;
        }
    }

    void dequeueComment()
    {
        if (frontComment == nullptr)
        {
            cout << "Tidak ada komentar untuk dihapus." << endl;
            return;
        }

        CommentNode *temp = frontComment;
        frontComment = frontComment->next;
        if (frontComment == nullptr)
        {
            rearComment = nullptr;
        }
        delete temp;
        // cout << "Komentar berhasil diproses dan dihapus dari antrian." << endl;
    }

    CommentNode *peek()
    {
        if (frontComment != nullptr)
            return frontComment;
        cout << "Antrian komentar kosong." << endl;
        return nullptr;
    }

    bool isEmpty()
    {
        return frontComment == nullptr;
    }
};

struct Article
{
    string id;
    string title;
    string content;
    string category;
    int commentCount = 0;

    CommentNode *commentsHead = nullptr;

    void showComments()
    {
        CommentNode *comment = commentsHead;
        if (comment == nullptr)
        {
            cout << "(Tidak ada komentar untuk artikel ini)." << endl;
        }
        else
        {
            while (comment != nullptr)
            {
                cout << "- " << comment->text << endl;
                comment = comment->next;
            }
        }
    }

    void addComment(string text)
    {

        CommentNode *newComment = new CommentNode(id, text);

        if (commentsHead == nullptr)
        {
            commentsHead = newComment;
        }
        else
        {
            CommentNode *temp = commentsHead;
            while (temp->next != nullptr)
                temp = temp->next;
            temp->next = newComment;
        }
        commentCount++;
    }
};

struct ArticleVertex
{
    Article *article;
    ArticleVertex *adj[MAX_ADJ];
    int adjCount = 0;
    bool visited = false;

    ArticleVertex(Article *a) : article(a) {}

    void addEdge(ArticleVertex *v)
    {
        if (adjCount < MAX_ADJ)
        {
            adj[adjCount++] = v;
        }
    }

    void removeEdge(ArticleVertex *v)
    {
        for (int i = 0; i < adjCount; i++)
        {
            if (adj[i] == v)
            {
                for (int j = i; j < adjCount - 1; j++)
                {
                    adj[j] = adj[j + 1];
                }
                adjCount--;
                break;
            }
        }
    }

    void showRelated()
    {
        cout << "Artikel terkait untuk " << article->title << ":" << endl;
        for (int i = 0; i < adjCount; i++)
        {
            cout << "- [ID: " << adj[i]->article->id << "] " << adj[i]->article->title << endl;
        }
    }

    Article *getFirstRelatedArticle()
    {
        if (adjCount > 0)
            return adj[0]->article;
        return nullptr;
    }

    bool isRelated(Article *a)
    {
        for (int i = 0; i < adjCount; i++)
        {
            if (adj[i]->article == a)
                return true;
        }
        return false;
    }
};

int compareWords(const string &a, const string &b)
{
    int len = min(a.length(), b.length());
    for (int i = 0; i < len; ++i)
    {
        char ca = tolower(a[i]);
        char cb = tolower(b[i]);

        if (ca < cb)
            return -1;
        if (ca > cb)
            return 1;
    }

    if (a.length() < b.length())
        return -1;
    if (a.length() > b.length())
        return 1;
    return 0;
}

struct ArticleGraph
{
    ArticleVertex *vertices[MAX_ARTICLE];
    int vertexCount = 0;

    void addArticle(Article *a)
    {
        if (vertexCount < MAX_ARTICLE)
        {
            vertices[vertexCount++] = new ArticleVertex(a);
        }
    }

    void addEdge(Article *a1, Article *a2)
    {
        ArticleVertex *v1 = findVertex(a1);
        ArticleVertex *v2 = findVertex(a2);

        if (v1 && v2)
        {
            v1->addEdge(v2);
            v2->addEdge(v1);
        }
    }

    ArticleVertex *findVertex(Article *a)
    {
        for (int i = 0; i < vertexCount; i++)
        {
            if (vertices[i]->article == a)
                return vertices[i];
        }
        return nullptr;
    }

    void removeArticle(Article *a)
    {
        ArticleVertex *v = findVertex(a);
        if (v)
        {
            for (int i = 0; i < v->adjCount; i++)
            {
                v->adj[i]->removeEdge(v);
            }

            delete v;

            for (int i = 0; i < vertexCount; i++)
            {
                if (vertices[i] == v)
                {
                    for (int j = i; j < vertexCount - 1; j++)
                    {
                        vertices[j] = vertices[j + 1];
                    }
                    vertexCount--;
                    break;
                }
            }
        }
    }

    void clear()
    {
        for (int i = 0; i < vertexCount; i++)
        {
            delete vertices[i];
        }
        vertexCount = 0;
    }

    void resetVisited()
    {
        for (int i = 0; i < vertexCount; i++)
        {
            vertices[i]->visited = false;
        }
    }

    void dfs(ArticleVertex *v)
    {
        if (v == nullptr || v->visited)
            return;

        v->visited = true;
        // cout << "Visited: " << v->article->title << endl;

        for (int i = 0; i < v->adjCount; i++)
        {
            if (!v->adj[i]->visited)
            {
                cout << "- " << v->article->title << " → " << v->adj[i]->article->title << endl;
                dfs(v->adj[i]);
            }
        }
    }

    ~ArticleGraph()
    {
        clear();
    }
};

struct HashEntry
{
    string id;
    Article *article;

    HashEntry(string i, Article *a) : id(i), article(a) {}
};

struct HashTable
{
    HashEntry *table[MAX_ARTICLE];
    int size;

    HashTable(int s) : size(s)
    {
        for (int i = 0; i < size; i++)
            table[i] = nullptr;
    }

    int hashFunction(string id)
    {
        int hash = 0;
        for (char c : id)
        {
            hash += c;
        }
        return hash % size;
    }

    void insert(string id, Article *article)
    {
        int index = hashFunction(id);
        while (table[index] != nullptr)
        {
            index = (index + 1) % size;
        }
        table[index] = new HashEntry(id, article);
    }

    Article *search(string id)
    {
        int index = hashFunction(id);
        while (table[index] != nullptr)
        {
            if (table[index]->id == id)
                return table[index]->article;
            index = (index + 1) % size;
        }
        return nullptr;
    }

    void remove(string id)
    {
        int index = hashFunction(id);
        while (table[index] != nullptr)
        {
            if (table[index]->id == id)
            {
                delete table[index];
                table[index] = nullptr;
                return;
            }
            index = (index + 1) % size;
        }
    }

    void clear()
    {
        for (int i = 0; i < size; i++)
        {
            if (table[i] != nullptr)
            {
                delete table[i];
                table[i] = nullptr;
            }
        }
    }

    ~HashTable()
    {
        clear();
    }
};

struct StackNode
{
    Article *article;
    StackNode *next;

    StackNode(Article *a) : article(a), next(nullptr) {}
};

struct HistoryStack
{
    StackNode *top = nullptr;

    void push(Article *a)
    {
        StackNode *newNode = new StackNode(a);
        newNode->next = top;
        top = newNode;
    }

    Article *pop()
    {
        if (isEmpty())
            return nullptr;

        StackNode *temp = top;
        Article *result = top->article;
        top = top->next;
        delete temp;
        return result;
    }

    Article *peek()
    {
        return isEmpty() ? nullptr : top->article;
    }

    bool isEmpty()
    {
        return top == nullptr;
    }

    ~HistoryStack()
    {
        while (!isEmpty())
        {
            pop();
        }
    }
};

struct TreeNode
{
    string category;
    Article *articles[MAX_ARTICLE];
    int articleCount;
    TreeNode *left;
    TreeNode *right;

    TreeNode(const string &cat)
    {
        category = cat;
        articleCount = 0;
        left = right = nullptr;
    }

    void showAllArticles()
    {
        if (!articleCount)
        {
            cout << "(Tidak ada artikel pada kategori ini)." << endl;
            return;
        }
        for (int i = 0; i < articleCount; i++)
        {
            cout << "- " << articles[i]->id << " - " << articles[i]->title << endl;
        }
    }
};

struct CategoryTree
{
    TreeNode *root = nullptr;

    void insert(const string &cat, Article *article)
    {
        root = insertRec(root, cat, article);
    }

    TreeNode *insertRec(TreeNode *node, const string &cat, Article *article)
    {
        if (node == nullptr)
        {
            TreeNode *newNode = new TreeNode(cat);
            newNode->articles[newNode->articleCount++] = article;
            return newNode;
        }

        int cmp = compareWords(cat, node->category);
        if (cmp < 0)
        {
            node->left = insertRec(node->left, cat, article);
        }
        else if (cmp > 0)
        {
            node->right = insertRec(node->right, cat, article);
        }
        else
        {
            node->articles[node->articleCount++] = article;
        }

        return node;
    }

    TreeNode *search(const string &cat)
    {
        return searchRec(root, cat);
    }

    TreeNode *searchRec(TreeNode *node, const string &cat)
    {
        if (node == nullptr || node->category == cat)
            return node;

        int cmp = compareWords(cat, node->category);
        if (cmp < 0)
            return searchRec(node->left, cat);
        else
            return searchRec(node->right, cat);
    }

    void inorder(TreeNode *node)
    {
        if (node == nullptr)
            return;

        inorder(node->left);
        cout << "- " << node->category << endl;
        inorder(node->right);
    }

    bool isEmpty()
    {
        return root == nullptr;
    }

    void showAll()
    {
        inorder(root);
    }

    void clearTree(TreeNode *node)
    {
        if (node == nullptr)
            return;
        clearTree(node->left);
        clearTree(node->right);
        delete node;
    }

    void clear()
    {
        clearTree(root);
        root = nullptr;
    }
};

Article articles[MAX_ARTICLE];
int articlesCount = 0;

HistoryStack historyStack;
CommentQueue commentQueue;
HashTable hashTable(MAX_ARTICLE);
ArticleGraph articleGraph;
CategoryTree categoryTree;

/* Begin visitor handler functions */
// 1. Lihat Semua Artikel
void showAllArticles()
{
    if (articlesCount == 0)
    {
        cout << "--- Belum ada artikel ---" << endl;
        return;
    }

    cout << "--- Daftar Artikel ---" << endl;
    for (int i = 0; i < articlesCount; i++)
    {
        cout << "[" << i + 1 << "] ";
        cout << "[ID: " << articles[i].id << "] ";
        cout << articles[i].title << endl;
    }

    cout << "Total artikel: " << articlesCount << endl;
}

// 2. Urutkan Artikel
void copyArray(Article source[], Article destination[], int count)
{
    for (int i = 0; i < count; i++)
    {
        destination[i] = source[i];
    }
}

int inputMenuSort()
{
    cout << "--- Urutkan Artikel ---" << endl;
    cout << "Urutkan berdasarkan:" << endl;
    cout << "1. Judul (A-Z)" << endl;
    cout << "2. Judul (Z-A)" << endl;
    cout << "3. ID Artikel (Ascending)" << endl;

    int pilihan = inputMenu();

    while (pilihan < 1 || pilihan > 3)
    {
        cout << "Pilihan tidak valid. Masukkan angka 1 - 3: ";
        pilihan = inputMenu();
    }

    return pilihan;
}

bool shouldSwap(const Article &a, const Article &b, int option)
{
    if (option == 1)
        // return a.title > b.title;
        return compareWords(a.title, b.title) > 0;
    else if (option == 2)
        // return a.title < b.title;
        return compareWords(a.title, b.title) < 0;
    else if (option == 3)
        return a.id > b.id;

    return false;
}

void bubbleSortArticles(Article a[], int count, int option)
{
    for (int i = 0; i < count - 1; i++)
    {
        for (int j = 0; j < count - i - 1; j++)
        {
            if (shouldSwap(a[j], a[j + 1], option))
            {
                Article temp = a[j];
                a[j] = a[j + 1];
                a[j + 1] = temp;
            }
        }
    }
}

void sortArticles()
{
    if (articlesCount == 0)
    {
        cout << "Belum ada artikel untuk diurutkan." << endl;
        return;
    }

    Article articlesCopy[MAX_ARTICLE];
    copyArray(articles, articlesCopy, articlesCount);

    int option = inputMenuSort();
    bubbleSortArticles(articlesCopy, articlesCount, option);

    cout << "--- Menampilkan Artikel Terurut ---" << endl;
    for (int i = 0; i < articlesCount; i++)
    {
        cout << "[" << i + 1 << "] ";
        cout << "[ID: " << articlesCopy[i].id << "] ";
        cout << articlesCopy[i].title << endl;
    }
    cout << "Total artikel: " << articlesCount << endl;
}

// 3. Cari dan Baca Artikel
int findArticleIndex(string keyword)
{
    for (int i = 0; i < articlesCount; i++)
    {
        if (articles[i].id == keyword || articles[i].title == keyword)
        {
            return i;
        }
    }
    return -1;
}

void previewArticle(Article *a)
{
    cout << endl
         << "Judul: " << a->title << endl;
    cout << "ID: " << a->id << endl;
    cout << "Kategori: " << a->category << endl;
    cout << "Jumlah Komentar: " << a->commentCount << endl;
}

void readArticle(Article *a)
{
    cout << endl
         << "--- Isi Artikel ---" << endl;
    cout << a->content << endl;
    cout << "----------------------------------------" << endl;
}

int binarySearchArticle(string title)
{
    int left = 0;
    int right = articlesCount - 1;

    while (left <= right)
    {
        int mid = left + (right - left) / 2;

        if (articles[mid].title == title)
            return mid;
        else if (articles[mid].title < title)
            left = mid + 1;
        else
            right = mid - 1;
    }
    return -1;
}

Article *searchArticle(string keyword)
{
    Article *article = nullptr;

    if (isArticleId(keyword))
    {
        article = hashTable.search(keyword);
    }
    else
    {
        int index = findArticleIndex(keyword);
        if (index == -1)
        {
            return nullptr;
        }
        article = &articles[index];
    }

    return article;
}

// TODO: Implementasi komentar artikel
void searchAndReadArticle()
{
    if (articlesCount == 0)
    {
        cout << "Belum ada artikel untuk dicari." << endl;
        return;
    }

    cout << "--- Cari dan Baca Artikel ---" << endl;

    string keyword = inputData("Masukkan ID / Judul Artikel");
    Article *article = searchArticle(keyword);

    if (article == nullptr)
    {
        cout << "Artikel tidak ditemukan." << endl;
        return;
    }

    previewArticle(article);

    bool isRead = inputYN("Baca artikel?");

    if (!isRead)
    {
        cout << "Artikel tidak dibaca." << endl;
        return;
    }

    readArticle(article);
    historyStack.push(article);

    bool isShowComments = inputYN("Tampilkan komentar artikel?");
    if (isShowComments)
    {
        cout << "--- Komentar Artikel ---" << endl;
        article->showComments();
    }
}

// 4. Tambahkan Komentar
void addComment()
{
    if (articlesCount == 0)
    {
        cout << "Belum ada artikel yang tersedia untuk dikomentari." << endl;
        return;
    }

    cout << "--- Tambahkan Komentar ---" << endl;
    string articleId = inputData("Masukkan ID Artikel: ");

    Article *article = hashTable.search(articleId);
    if (article == nullptr)
    {
        cout << "Artikel tidak ditemukan." << endl;
        return;
    }

    string text = inputData("Masukkan komentar Anda");
    commentQueue.enqueueComment(articleId, text);
    cout << "Komentar berhasil ditambahkan ke antrian." << endl;
}

// 5. Lihat Riwayat Bacaan
void showReadingHistory()
{
    if (historyStack.isEmpty())
    {
        cout << "Belum ada riwayat bacaan." << endl;
        return;
    }

    StackNode *temp = historyStack.top;
    int count = 1;
    cout << "--- Riwayat Artikel Dibaca (Terbaru ke Lama) ---" << endl;
    while (temp != nullptr)
    {
        cout << count++ << ". " << temp->article->title << endl;
        temp = temp->next;
    }

    cout << "(Tekan 'B' untuk kembali ke artikel sebelumnya)" << endl;
    char input = inputChar("Pilih");
    if (toupper(input) == 'B')
    {
        historyStack.pop();
        Article *prev = historyStack.peek();
        if (prev)
        {
            cout << "Kembali ke artikel: " << prev->title << endl;
            readArticle(prev);
            // cout << prev->content << endl;
            // showArticleComments(*prev);
        }
        else
        {
            cout << "Tidak ada artikel sebelumnya." << endl;
        }
    }
}

// 6. Jelajahi Topik Terkait
void readFullArticle(Article *article)
{
    previewArticle(article);
    readArticle(article);
    historyStack.push(article);
}

// Procedure DFS(node):
//     visited[node] ← true
//     Process(node)

//     For each neighbor in Adjacent(node):
//         If not visited[neighbor]:
//             DFS(neighbor)
void dfsExplore(ArticleVertex *root)
{
    if (root == nullptr)
    {
        return;
    }

    root->visited = true;
    for (int i = 0; i < root->adjCount; i++)
    {
        if (!root->adj[i]->visited)
        {
            cout << "- " << root->article->id << " -> " << root->adj[i]->article->id << endl;
            readFullArticle(root->adj[i]->article);
            cout << endl;

            bool isContinue = inputYN("Lanjut Jelajah?");
            if (!isContinue)
            {
                cout << "Eksplorasi dihentikan." << endl;
                return;
            }

            dfsExplore(root->adj[i]);
        }
    }
}

void exploreRelatedTopics()
{
    if (articleGraph.vertexCount == 0)
    {
        cout << "Belum ada artikel terkait yang tersedia." << endl;
        return;
    }
    string targetId = inputData("Masukkan ID Artikel");
    Article *article = hashTable.search(targetId);
    ArticleVertex *vertex = articleGraph.findVertex(article);

    if (vertex == NULL)
    {
        cout << "Artikel tidak ditemukan.\n";
        return;
    }

    Article *firstRelated = vertex->getFirstRelatedArticle();
    if (firstRelated == nullptr)
    {
        cout << endl
             << "Tidak ada artikel terkait untuk " << article->id << "." << endl;
        return;
    }

    articleGraph.resetVisited();
    cout << endl
         << "Hasil DFS:" << endl;
    dfsExplore(vertex);
    cout << endl
         << "Eksplorasi selesai." << endl;
}

// 7. Jelajahi Kategori Artikel
int linearSearchString(string arr[], int size, string target)
{
    for (int i = 0; i < size; i++)
    {
        if (arr[i] == target)
            return i;
    }
    return -1;
}

void getUniqueCategories(Article articles[], int count, string uniqueCategories[], int &uniqueCount)
{
    for (int i = 0; i < count; i++)
    {
        if (linearSearchString(uniqueCategories, uniqueCount, articles[i].category) == -1)
        {
            uniqueCategories[uniqueCount++] = articles[i].category;
        }
    }
}

void exploreCategories()
{
    if (categoryTree.isEmpty())
    {
        cout << "Belum ada kategori artikel." << endl;
        return;
    }
    cout << "--- Kategori Artikel ---" << endl;
    categoryTree.showAll();

    string inputCategory = inputData("Masukkan nama kategori yang ingin dijelajahi");

    TreeNode *categoryNode = categoryTree.search(inputCategory);
    if (categoryNode == nullptr)
    {
        cout << "Kategori '" << inputCategory << "' tidak ditemukan." << endl;
        return;
    }

    cout << "--- Menampilkan Artikel ---" << endl;
    categoryNode->showAllArticles();
}
/* End visitor handler functions */

/* Begin editor handler functions */
// 2. Tambah Artikel
Article createArticle()
{
    Article newArticle;
    newArticle.id = inputId("Masukkan ID Artikel");
    if (hashTable.search(newArticle.id) != nullptr)
    {
        cout << "ID Artikel sudah ada. Silakan gunakan ID yang berbeda." << endl;
        return createArticle();
    }

    newArticle.title = inputData("Masukkan Judul Artikel");
    newArticle.content = inputData("Masukkan Isi Artikel");
    newArticle.category = inputData("Masukkan Kategori Artikel");
    newArticle.commentCount = 0;

    return newArticle;
}

int inputRelatedCount()
{
    string label = "Masukkan jumlah artikel terkait (0 - " + to_string(MAX_ADJ) + ")";
    int count = inputInteger(label);

    if (count < 0 || count > MAX_ADJ)
    {
        cout << "Jumlah tidak valid." << endl;
        return inputRelatedCount();
    }

    if (articleGraph.vertexCount - 1 < count)
    {
        cout << "Jumlah terlalu besar. Jumlah artikel yang dapat dikaitkan hanya " << to_string(articleGraph.vertexCount - 1) << endl;
        return inputRelatedCount();
    }

    return count;
}

void addArticleToAllStructures(Article *article)
{
    categoryTree.insert(article->category, article);
    hashTable.insert(article->id, article);
    articleGraph.addArticle(article);
}

void connectRelatedArticles(Article *article)
{
    ArticleVertex *vertex = articleGraph.findVertex(article);

    cout << "--- Hubungkan Artikel Terkait ---" << endl;
    int relatedCount = inputRelatedCount();

    if (relatedCount == 0)
    {
        cout << "Tidak ada artikel terkait yang akan dihubungkan." << endl;
        return;
    }

    int count = 0;
    while (count < relatedCount)
    {
        string relatedId = inputId("Masukkan ID Artikel Terkait " + to_string(count + 1));
        Article *relatedArticle = hashTable.search(relatedId);

        if (relatedArticle == nullptr)
        {
            cout << "Artikel dengan ID " << relatedId << " tidak ditemukan." << endl;
            continue;
        }

        if (relatedArticle == article)
        {
            cout << "Tidak dapat menghubungkan artikel dengan dirinya sendiri." << endl;
            continue;
        }

        if (vertex->isRelated(relatedArticle))
        {
            cout << "Artikel ini sudah terkait dengan " << relatedArticle->title << "." << endl;
            continue;
        }

        articleGraph.addEdge(article, relatedArticle);
        count++;

        cout << "Artikel " << article->title << " berhasil dihubungkan dengan " << relatedArticle->title << "." << endl;
    }

    cout << endl
         << "Total artikel terkait yang dihubungkan: " << count << endl;
}

void addArticle()
{
    if (articlesCount >= MAX_ARTICLE)
    {
        cout << "Tidak dapat menambah artikel. Kapasitas maksimum tercapai." << endl;
        return;
    }

    cout << "--- Tambah Artikel ---" << endl;
    Article newArticle = createArticle();
    articles[articlesCount++] = newArticle;
    Article *articlePtr = &articles[articlesCount - 1];
    addArticleToAllStructures(articlePtr);

    cout << endl
         << "Artikel berhasil ditambahkan." << endl;

    if (articleGraph.vertexCount > 1)
    {
        connectRelatedArticles(articlePtr);
    }
}

void generateDummyArticles()
{
    string randomIds[15] = {
        "A001", "A002", "A003", "A004", "A005",
        "A006", "A007", "A008", "A009", "A010",
        "A011", "A012", "A013", "A014", "A015"};
    string randomTitles[15] = {
        "Artikel Pertama", "Artikel Kedua", "Artikel Ketiga",
        "Artikel Keempat", "Artikel Kelima", "Artikel Keenam",
        "Artikel Ketujuh", "Artikel Kedelapan", "Artikel Kesembilan",
        "Artikel Kesepuluh", "Artikel Kesebelas", "Artikel Keduabelas",
        "Artikel Ketigabelas", "Artikel Keempatbelas", "Artikel Kelimabelas"};
    string randomContents[15] = {
        "Ini adalah isi artikel pertama.",
        "Ini adalah isi artikel kedua.",
        "Ini adalah isi artikel ketiga.",
        "Ini adalah isi artikel keempat.",
        "Ini adalah isi artikel kelima.",
        "Ini adalah isi artikel keenam.",
        "Ini adalah isi artikel ketujuh.",
        "Ini adalah isi artikel kedelapan.",
        "Ini adalah isi artikel kesembilan.",
        "Ini adalah isi artikel kesepuluh.",
        "Ini adalah isi artikel kesebelas.",
        "Ini adalah isi artikel keduabelas.",
        "Ini adalah isi artikel ketigabelas.",
        "Ini adalah isi artikel keempatbelas.",
        "Ini adalah isi artikel kelimabelas."};
    string randomCategories[5] = {"Teknologi", "Kesehatan", "Olahraga", "Politik", "Ekonomi"};

    for (int i = 0; i < 15; i++)
    {
        Article dummyArticle;
        dummyArticle.id = randomIds[i];
        dummyArticle.title = randomTitles[i];
        dummyArticle.content = randomContents[i];
        dummyArticle.category = randomCategories[i % 5];
        dummyArticle.commentCount = 0;

        articles[articlesCount++] = dummyArticle;
        addArticleToAllStructures(&articles[articlesCount - 1]);
    }
}

// 3. Cari dan Edit Artikel
void editArticle(Article *article)
{
    cout << "[ID: " << article->id << "] " << article->title << endl;

    bool isEditTitle = inputYN("Edit judul?");
    if (isEditTitle)
    {
        article->title = inputData("Masukkan Judul Baru");
    }

    bool isEditContent = inputYN("Edit isi artikel?");
    if (isEditContent)
    {
        article->content = inputData("Masukkan Isi Baru");
    }

    cout << "Artikel berhasil diperbarui." << endl;
}

void searchAndEditArticle()
{
    if (articlesCount == 0)
    {
        cout << "Belum ada artikel untuk dicari." << endl;
        return;
    }

    cout << "--- Cari dan Edit Artikel ---" << endl;

    string keyword = inputData("Masukkan ID / Judul Artikel");
    Article *article = searchArticle(keyword);

    if (article == nullptr)
    {
        cout << "Artikel tidak ditemukan." << endl;
        return;
    }

    previewArticle(article);
    editArticle(article);
}

// 5. Komentar Masuk
void addProcessedCommentToArticle(string articleId, string commentText)
{
    Article *article = hashTable.search(articleId);
    if (article == nullptr)
    {
        cout << "Artikel dengan ID " << articleId << " tidak ditemukan." << endl;
        return;
    }

    article->addComment(commentText);
}

int inputCommentAction()
{
    cout << "Pilih aksi:" << endl;
    cout << "1. Proses komentar" << endl;
    cout << "2. Hapus komentar" << endl;
    cout << "0. Kembali" << endl;

    int choice = inputMenu();
    while (choice < 0 || choice > 2)
    {
        cout << "Pilihan tidak valid. Masukkan angka 0 - 2." << endl;
        choice = inputMenu();
    }

    return choice;
}

void showPendingComments()
{
    if (commentQueue.frontComment == nullptr)
    {
        cout << "Tidak ada komentar masuk.\n";
        return;
    }

    while (commentQueue.frontComment != nullptr)
    {
        cout << "\n--- Komentar Masuk ---\n";
        cout << "Artikel ID: " << commentQueue.frontComment->articleId << endl;
        cout << "Komentar   : " << commentQueue.frontComment->text << endl;

        int action = inputCommentAction();

        switch (action)
        {
        case 1:
            addProcessedCommentToArticle(commentQueue.frontComment->articleId, commentQueue.frontComment->text);
            commentQueue.dequeueComment();
            cout << "Komentar telah diproses dan ditambahkan ke artikel." << endl;
            break;
        case 2:
            commentQueue.dequeueComment();
            cout << "Komentar telah dihapus dari antrian." << endl;
            break;
        case 0:
            break;
        default:
            break;
        }

        if (action == 0)
            break;
    }
}

/* End editor handler functions */

void visitorPage()
{
    int choice;

    do
    {
        outputHeaderVisitor();
        choice = inputMenu();
        switch (choice)
        {
        case 1:
            showAllArticles();
            break;
        case 2:
            sortArticles();
            break;
        case 3:
            searchAndReadArticle();
            break;
        case 4:
            addComment();
            break;
        case 5:
            showReadingHistory();
            break;
        case 6:
            exploreRelatedTopics();
            break;
        case 7:
            exploreCategories();
            break;
        case 0:
            cout << "Kembali ke menu utama..." << endl;
            break;
        default:
            cout << "option " << choice << " tidak ditemukan" << endl;
            break;
        }
    } while (choice != 0);
}

void editorPage()
{
    int choice;

    do
    {
        outputHeaderEditor();
        choice = inputMenu();
        switch (choice)
        {
        case 1:
            showAllArticles();
            break;
        case 2:
            addArticle();
            break;
        case 3:
            searchAndEditArticle();
            break;
        case 4:
            sortArticles();
            break;
        case 5:
            showPendingComments();
            break;
        case 0:
            cout << "Kembali ke menu utama..." << endl;
            break;
        default:
            cout << "option " << choice << " tidak ditemukan" << endl;
            break;
        }
    } while (choice != 0);
}

int main()
{
    generateDummyArticles();
    int choice;

    do
    {
        outputMainHeader();
        choice = inputMenu();
        switch (choice)
        {
        case 1:
            visitorPage();
            break;
        case 2:
            editorPage();
            break;
        case 0:
            cout << "Terima kasih telah menggunakan sistem ini. Sampai jumpa!" << endl;
            break;
        default:
            cout << "option " << choice << " tidak ditemukan" << endl;
            break;
        }
    } while (choice != 0);

    return 0;
}