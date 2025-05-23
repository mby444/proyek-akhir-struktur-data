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
    cout << "4. Urutkan Artikel" << endl;
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
    cout << "2. Urutkan Artikel" << endl;
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
    cin.ignore();
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
    }
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
            cout << "Tidak ada komentar untuk diproses." << endl;
            return;
        }

        CommentNode *temp = frontComment;
        frontComment = frontComment->next;
        if (frontComment == nullptr)
        {
            rearComment = nullptr;
        }
        delete temp;
        cout << "Komentar berhasil diproses dan dihapus dari antrian." << endl;
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
    // string relatedIds[MAX_ADJ];
    // int relatedCount;
    int commentCount = 0;

    CommentNode *commentsHead = nullptr;
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
};

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

        if (cat < node->category)
        {
            node->left = insertRec(node->left, cat, article);
        }
        else if (cat > node->category)
        {
            node->right = insertRec(node->right, cat, article);
        }
        else
        {
            node->articles[node->articleCount++] = article;
        }

        return node;
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
        cin >> pilihan;
    }

    return pilihan;
}

bool shouldSwap(const Article &a, const Article &b, int option)
{
    if (option == 1)
        return a.title > b.title;
    else if (option == 2)
        return a.title < b.title;
    else if (option == 3)
        return a.id > b.id;

    return false;
}

void bubbleSortArticles(int option)
{
    for (int i = 0; i < articlesCount - 1; i++)
    {
        for (int j = 0; j < articlesCount - i - 1; j++)
        {
            if (shouldSwap(articles[j], articles[j + 1], option))
            {
                Article temp = articles[j];
                articles[j] = articles[j + 1];
                articles[j + 1] = temp;
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

    int option = inputMenuSort();
    bubbleSortArticles(option);
    cout << "Artikel berhasil diurutkan." << endl;
    showAllArticles();
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
        bubbleSortArticles(1);
        int index = binarySearchArticle(keyword);
        if (index == -1)
        {
            return nullptr;
        }
        article = &articles[index];
    }

    return article;
}

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
            cout << prev->content << endl;
            // showArticleComments(*prev);
        }
        else
        {
            cout << "Tidak ada artikel sebelumnya." << endl;
        }
    }
}

// 6. Jelajahi Topik Terkait
// bool visited[MAX_ARTICLE];

// Procedure DFS(node):
//     visited[node] ← true
//     Process(node)

//     For each neighbor in Adjacent(node):
//         If not visited[neighbor]:
//             DFS(neighbor)
void dfsExplore(Article *article)
{
    // if (article == nullptr)
    //     return;

    // visited[findArticleIndex(article->id)] = true;

    // for (int i = 0; i < article->relatedCount; ++i)
    // {
    //     Article* next = searchArticleById(article->related[i]);
    //     if (next && !visited[getArticleIndex(next->id)])
    //     {
    //         cout << "- " << article->id << " → " << next->id << "\n";
    //         dfsExplore(next);
    //     }
    // }
}

void exploreRelatedTopics()
{
    // string targetId = inputData("Masukkan ID Artikel");
    // Article* root = searchArticleById(targetId);

    // if (root == NULL)
    // {
    //     cout << "Artikel tidak ditemukan.\n";
    //     return;
    // }

    // // Reset visited array
    // for (int i = 0; i < MAX_ARTICLES; ++i)
    //     visited[i] = false;

    // cout << "\nHasil DFS:\n";
    // dfsExplore(root);

    // string bacaId = inputData("Ingin baca artikel tertentu? Masukkan ID (kosongkan untuk batal)");
    // if (bacaId.empty())
    //     return;

    // Article* selected = searchArticleById(bacaId);
    // if (selected)
    // {
    //     cout << "\nMenampilkan: " << selected->title << "\n";
    //     cout << selected->content << "\n";
    //     readHistory.push(selected);
    //     showArticleComments(*selected);
    // }
    // else
    // {
    //     cout << "Artikel tidak ditemukan.\n";
    // }
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
    cout << "--- Kategori Artikel ---\n\n";

    // Inisialisasi array kategori unik
    string uniqueCategories[MAX_ARTICLE];
    int categoryCount = 0;

    // Kumpulkan semua kategori yang unik
    getUniqueCategories(articles, articlesCount, uniqueCategories, categoryCount);

    // Tampilkan kategori beserta artikel-artikelnya
    for (int i = 0; i < categoryCount; i++)
    {
        cout << "- " << uniqueCategories[i] << endl;
        for (int j = 0; j < articlesCount; j++)
        {
            if (articles[j].category == uniqueCategories[i])
            {
                cout << "  - " << articles[j].id << " - " << articles[j].title << endl;
            }
        }
    }

    // Input nama kategori
    string inputCategory = inputData("Masukkan kategori");

    // Tampilkan artikel pada kategori tersebut
    cout << "Menampilkan artikel:\n";
    bool found = false;
    for (int i = 0; i < articlesCount; i++)
    {
        if (articles[i].category == inputCategory)
        {
            cout << "- " << articles[i].id << " - " << articles[i].title << endl;
            found = true;
        }
    }

    if (!found)
    {
        cout << "(Tidak ada artikel dalam kategori ini)" << endl;
    }
}

/* End visitor handler functions */

/* Begin editor handler functions */
// 2. Tambah Artikel
Article createArticle()
{
    // Article newArticle;
    // newArticle.id = inputData("Masukkan ID Artikel");
    // newArticle.title = inputData("Masukkan Judul Artikel");
    // newArticle.content = inputData("Masukkan Isi Artikel");
    // newArticle.category = inputData("Masukkan Kategori Artikel");
    // // newArticle.relatedCount = input;
    // newArticle.commentCount = 0;

    // return newArticle;
}
void addArticle()
{
    // if (articlesCount >= MAX_ARTICLE)
    // {
    //     cout << "Tidak dapat menambah artikel. Kapasitas maksimum tercapai." << endl;
    //     return;
    // }
}

// 3. Cari dan Edit Artikel
void editArticle(Article *article)
{
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
    int index = findArticleIndex(keyword);

    if (index == -1)
    {
        cout << "Artikel tidak ditemukan." << endl;
        return;
    }

    Article *a = &articles[index];
    editArticle(a);
}

// 5. Komentar Masuk
void addProcessedCommentToArticle(string articleId, string commentText)
{
    int idx = findArticleIndex(articleId);
    if (idx == -1)
        return;

    CommentNode *newComment = new CommentNode(articleId, commentText);

    if (articles[idx].commentsHead == nullptr)
    {
        articles[idx].commentsHead = newComment;
    }
    else
    {
        CommentNode *temp = articles[idx].commentsHead;
        while (temp->next != nullptr)
            temp = temp->next;
        temp->next = newComment;
    }
}

void showPendingComments()
{
    if (commentQueue.frontComment == nullptr)
    {
        cout << "Tidak ada komentar masuk.\n";
        return;
    }

    // while (commentQueue.frontComment != nullptr)
    // {
    // cout << "\n--- Antrian Komentar ---\n";
    // cout << "Artikel ID: " << commentQueue.frontComment->articleId << endl;
    // cout << "Komentar   : " << commentQueue.frontComment->text << endl;

    // bool process = inputYN("Proses komentar ini? (Y/N): ");
    // if (process)
    // {
    //     // Tambahkan komentar ke artikel terkait
    //     addProcessedCommentToArticle(commentsFront->articleId, commentsFront->text);

    //     // Hapus dari antrian
    //     CommentQueueNode *toDelete = commentsFront;
    //     commentsFront = commentsFront->next;
    //     if (commentsFront == nullptr)
    //         commentsRear = nullptr;

    //     delete toDelete;
    //     cout << "Komentar telah diproses dan ditambahkan ke artikel.\n";
    // }
    // else
    // {
    //     cout << "Komentar tidak diproses.\n";
    //     break;
    // }
    // }
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