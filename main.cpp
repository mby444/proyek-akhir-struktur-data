#include <iostream>
#include <string>
#include <cstdint>

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
    cout << "2. Urutkan Artikel" << endl;
    cout << "3. Tambah Artikel" << endl;
    cout << "4. Cari dan Edit Artikel" << endl;
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

struct CommentNode
{
    string articleId;
    string text;
    CommentNode *next;
};

struct Article
{
    string id;
    string title;
    string content;
    string category;
    string relatedIds[MAX_ADJ];
    int relatedCount;
    int commentCount = 0;

    CommentNode *commentsHead = nullptr;
};

struct HashEntry
{
    string id;
    Article *articlePtr;
};

struct StackNode
{
    Article *article;
    StackNode *next;

    StackNode(Article *a) : article(a), next(nullptr) {}
};

struct Stack
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

    ~Stack()
    {
        while (!isEmpty())
        {
            pop();
        }
    }
};

struct CommentQueue
{
    CommentNode *frontComment = nullptr;
    CommentNode *rearComment = nullptr;

    void enqueueComment(string articleId, string text)
    {
        CommentNode *newNode = new CommentNode;
        newNode->articleId = articleId;
        newNode->text = text;
        newNode->next = nullptr;

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
        if (root == nullptr)
        {
            root = new TreeNode(cat);
            root->articles[root->articleCount++] = article;
        }
        else
        {
            insertRec(root, cat, article);
        }
    }

    void insertRec(TreeNode *node, const string &cat, Article *article)
    {
        if (cat < node->category)
        {
            if (node->left == nullptr)
            {
                node->left = new TreeNode(cat);
                node->left->articles[node->left->articleCount++] = article;
            }
            else
            {
                insertRec(node->left, cat, article);
            }
        }
        else if (cat > node->category)
        {
            if (node->right == nullptr)
            {
                node->right = new TreeNode(cat);
                node->right->articles[node->right->articleCount++] = article;
            }
            else
            {
                insertRec(node->right, cat, article);
            }
        }
        else
        {
            node->articles[node->articleCount++] = article;
        }
    }
};

struct GraphNode
{
    Article *article;
    GraphNode *adj[MAX_ADJ];
    int adjCount = 0;
};

Article articles[MAX_ARTICLE];
int articlesCount = 0;

Stack historyStack;
CommentQueue commentQueue;

/* Begin helper functions */
/* End helper functions */

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

void readArticle(Article *a)
{
    cout << endl
         << "[ID: " << a->id << "] " << a->title << endl;
    cout << "Kategori : " << a->category << endl;
    cout << "Topik Terkait: ";

    for (int i = 0; i < a->relatedCount; i++)
    {
        cout << a->relatedIds[i];
        if (i < a->relatedCount - 1)
            cout << ", ";
    }
    cout << endl
         << "Isi:" << endl
         << a->content << endl;
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
    int index = findArticleIndex(keyword);

    if (index == -1)
    {
        cout << "Artikel tidak ditemukan." << endl;
        return;
    }

    Article *a = &articles[index];

    readArticle(a);
    historyStack.push(a);
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

    int index = findArticleIndex(articleId);
    if (index == -1)
    {
        cout << "Artikel dengan ID tersebut tidak ditemukan." << endl;
        return;
    }

    string text = inputData("Masukkan komentar Anda: ");
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

    CommentNode *newComment = new CommentNode;
    newComment->text = commentText;
    newComment->next = nullptr;

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