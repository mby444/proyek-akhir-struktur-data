# **Data Structure Explorer**

---

### **Tampilan Awal**

```
======================================
      DATA STRUCTURE EXPLORER
  Sistem Mini-Ensklopedia Interaktif
======================================
1. Masuk Sebagai Pengunjung
2. Masuk Sebagai Editor
0. Keluar
Pilih menu: _
```

---

### **Peran: PENGUNJUNG**

```
======================================
      DATA STRUCTURE EXPLORER
            -- Pengunjung --
======================================
1. Lihat Semua Artikel
2. Urutkan Artikel
3. Cari dan Baca Artikel
4. Tambahkan Komentar
5. Lihat Riwayat Bacaan
6. Jelajahi Topik Terkait
7. Jelajahi Kategori Artikel
0. Kembali
Pilih menu: _
```

---

#### 1. Lihat Semua Artikel

(Menggunakan: `Struct`, `Array`)

```
--- Daftar Artikel ---
[ID: A001] Pengenalan Linked List
[ID: A002] Konsep Stack dan Queue
[ID: A003] Hash Table dan Implementasinya
Total artikel: 3
Tekan Enter untuk kembali...
```

---

#### 2. Urutkan Artikel

(Menggunakan: `Sorting` – Merge Sort, Bubble Sort)

```
--- Urutkan Artikel ---
Urut berdasarkan:
1. Judul (A-Z)
2. Judul (Z-A)
3. ID Artikel (Ascending)
Pilih: 1

Hasil:
[ID: A002] Konsep Stack dan Queue
[ID: A001] Pengenalan Linked List
[ID: A003] Hash Table dan Implementasinya
```

---

#### 3. Cari dan Baca Artikel

(Menggunakan: `Hash Table`, `Searching`)

```
--- Cari Artikel ---
Masukkan ID / Judul: A001

Hasil:
[ID: A001] Pengenalan Linked List
Kategori: Struktur Linear
Topik Terkait: A002
Komentar: 2

Baca artikel? (Y/N): Y

[Isi Artikel Ditampilkan]

Tampilkan komentar? (Y/N): Y

[Isi komentar ditampilkan]

Masukkan ke riwayat bacaan... Berhasil.
```

---

#### 4. Tambahkan Komentar

(Menggunakan: `Queue`)

```
--- Tambah Komentar ---
ID Artikel: A003
Komentar: Penjelasan hash collision-nya masih bingung...

Komentar berhasil ditambahkan. Akan ditinjau oleh Editor.
```

---

#### 5. Lihat Riwayat Bacaan

(Menggunakan: `Stack`)

```
--- Riwayat Bacaan ---
1. Hash Table dan Implementasinya
2. Pengenalan Linked List

Tekan 'B' untuk kembali ke artikel sebelumnya
Pilihan: B
Membuka: Pengenalan Linked List
```

---

#### 6. Jelajahi Topik Terkait

(Menggunakan: `Graph`, `DFS rekursif`)

```
--- Topik Terkait ---
Masukkan ID Artikel: A001

Hasil DFS:
- A001 → A002
- A002 → A003

Ingin baca A002? (Y/N): Y
Menampilkan: Konsep Stack dan Queue
--- Isi Artikel ---
Blah blah blah
-----------------------

Lanjut jelajahi topik terkait A002?> (Y/N): Y

Hasil DFS:
- A002 → A003

Ingin baca A003? (Y/N): Y

Menampilkan: Konsep Tree
--- Isi Artikel ---
Blah blah blah
-----------------------

Tidak ada topik terkait selanjutnya untuk dijelajahi.
```

#### 6. Jelajahi Topik Terkait (Alternatif)

(Menggunakan: `Graph`, `DFS rekursif`)

```
--- Topik Terkait ---
Masukkan ID Artikel: A001

Hasil DFS:
- A001 → A002
Judul: Konsep Tree
Kategori: Struktur Hirarki
Jumlah Komentar: 0

--- Isi Artikel ---
Blah blah blah blah blah blah blah.

Lanjut Jelajah? (Y/N): y
- A002 → A003
Judul: Konsep Stack
Kategori: Struktur Linear
Jumlah Komentar: 1

--- Isi Artikel ---
Blah blah blah blah blah blah blah.

Semua artikel terkait sudah dijelajahi.
```

---

#### 7. Jelajahi Kategori Artikel

(Menggunakan: `Tree`, `Recursion`)

```
--- Kategori Artikel ---

- Struktur Linear
  - A001 - Pengenalan Linked List
  - A002 - Konsep Stack dan Queue
- Struktur Asosiatif
  - A003 - Hash Table dan Implementasinya

Masukkan kategori: Struktur Linear

Menampilkan artikel:
- A001 - Pengenalan Linked List
- A002 - Konsep Stack dan Queue
```

---

### **Peran: EDITOR**

```
======================================
      DATA STRUCTURE EXPLORER
              -- Editor --
======================================
1. Lihat Semua Artikel
2. Tambah Artikel
3. Cari dan Edit Artikel
4. Urutkan Artikel
5. Komentar Masuk
0. Kembali
Pilih menu: _
```

---

#### 2. Tambah Artikel

(Menggunakan: `Struct`, `Hash Table`, `Array`, `Graph`)

```
--- Tambah Artikel Baru ---
ID Artikel: A004
Judul     : Tree dalam File System
Isi       : Tree digunakan untuk struktur direktori...
Kategori  : Struktur Hirarki
Topik Terkait (pisahkan koma): A001,A003

Artikel berhasil ditambahkan!
```

#### 2. Tambah Artikel (Alternatif)

(Menggunakan: `Struct`, `Hash Table`, `Array`, `Graph`)

```
--- Tambah Artikel Baru ---
ID Artikel: A004
Judul     : Tree dalam File System
Isi       : Tree digunakan untuk struktur direktori...
Kategori  : Struktur Hirarki
Artikel berhasil ditambahkan!

--- Hubungkan dengan Topik Terkait ---
Jumlah Topik Terkait (Ketik 0 Jika Tidak Ada): 3
- ID Topik Terkait 1: A001
Berhasil mengaitkan topik: A004 <-> A001
- ID Topik Terkait 2: A003
Berhasil mengaitkan topik: A004 <-> A003
- ID Topik Terkait 3: A005
Artikel dengan ID A005 tidak ditemukan.
- ID Topik Terkait 3: A002
Berhasil mengaitkan topik: A004 <-> A002

Artikel berhasil dihubungkan dengan 3 topik terkait!

```

Catatan:

- Jumlah maksimal artikel terkait adalah 10.
- Terdapat validasi dan pengecekan apakah artikel dengan id yang sama seperti yang dimasukkan ada.

---

#### 3. Cari dan Edit Artikel

(Menggunakan: `Hash Table`, `Searching`)

```
--- Cari Artikel untuk Diedit ---
Masukkan ID / Judul: A002

[ID: A002] Konsep Stack dan Queue
Edit Judul (Y/N)? Y
Judul Baru: Stack vs Queue dalam Kehidupan

Update berhasil.
```

---

#### 5. Komentar Masuk

(Menggunakan: `Queue`)

```
--- Komentar Masuk ---
1. A003 - "Penjelasan hash collision-nya masih bingung..."
2. A001 - "Artikel ini sangat membantu!"

Pilih aksi:
1. Tampilkan komentar pertama
2. Proses dan hapus komentar pertama
Pilihan: 1

A003: "Penjelasan hash collision-nya masih bingung..."
```

---

### **Struktur Data yang Diimplementasikan:**

| No  | Materi Struktur Data | Fitur yang Menggunakannya                 |
| --- | -------------------- | ----------------------------------------- |
| 1   | Pointer & Struct     | Semua fitur data (artikel, komentar)      |
| 2   | Linked List          | Penyimpanan dinamis riwayat atau komentar |
| 3   | Stack                | Riwayat Bacaan                            |
| 4   | Queue                | Komentar Masuk                            |
| 5   | Recursion            | Tree traversal & DFS Graph                |
| 6   | Sorting              | Urutkan Artikel                           |
| 7   | Searching            | Cari Artikel                              |
| 8   | Hash Table           | Akses cepat berdasarkan ID Artikel        |
| 9   | Tree                 | Kategori Artikel                          |
| 10  | Graph                | Topik Terkait antar artikel               |
