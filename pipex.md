# Pipex

**Goal:**  
This project focuses on handling **Unix pipes (`|`)** and connecting multiple shell commands together.

---

## 🧾 Description

Your program must take **4 arguments**:

```bash
./pipex file1 cmd1 cmd2 file2
```

- `file1` → input file  
- `file2` → output file  
- `cmd1`, `cmd2` → shell commands with their parameters  

The program should behave **exactly like** the following shell command:

```bash
< file1 cmd1 | cmd2 > file2
```

---

## 🧪 Examples

```bash
./pipex infile "ls -l" "wc -l" outfile
```

Equivalent to:
```bash
< infile ls -l | wc -l > outfile
```

```bash
./pipex infile "grep a1" "wc -w" outfile
```

Equivalent to:
```bash
< infile grep a1 | wc -w > outfile
```

---

## ⚙️ Requirements

- You must submit a **Makefile** that compiles your source files.  
  - It must not perform unnecessary relinking.  
- Your program must **never terminate unexpectedly** (e.g., segmentation fault, bus error, double free, etc.).  
- Your program must **not have memory leaks**.  
- If you are unsure, handle errors the same way as the shell command:

```bash
< file1 cmd1 | cmd2 > file2
```

---

## 💡 Bonus Part

### Multiple Pipes

Your program should handle **multiple pipes**:

```bash
./pipex file1 cmd1 cmd2 cmd3 ... cmdn file2
```

Which should behave like:

```bash
< file1 cmd1 | cmd2 | cmd3 ... | cmdn > file2
```

---

### Here Document Support

When the first argument is `"here_doc"`, your program must support `<<` and `>>` redirections.

```bash
./pipex here_doc LIMITER cmd cmd1 file
```

Which should behave like:

```bash
cmd << LIMITER | cmd1 >> file
```

---

# 🧩 Pipex Projesi — Makrolar ve Sabitler Özeti

| Kategori | Makrolar / Değerler | Dosyalar | Amaç |
|-----------|---------------------|-----------|-------|
| **Header guard makroları** | `PARSER_H`, `PIPEX_H`, `PIPEX_UTILS_H` | parser.h, pipex_utils.h, bonus/parser.h, bonus/pipex.h, bonus/pipex_utils/pipex_utils.h | Aynı header dosyasının birden fazla kez include edilmesini önler (`#ifndef / #define / #endif`). |
| **open() bayrakları** *(fcntl.h)* | `O_RDONLY`, `O_WRONLY`, `O_CREAT`, `O_TRUNC`, `O_APPEND` | main.c, open_file.c, here_doc.c, file_utils.c | `open()` çağrılarında dosya açma modlarını belirtir (okuma, yazma, oluşturma, truncate, ekleme). |
| **Dosya izin modu sayısı** | `0644` | main.c, here_doc.c, file_utils.c, Makefile | Yeni oluşturulan dosyaların UNIX izinlerini belirtir (`rw-r--r--`). |
| **access() sabitleri** *(unistd.h)* | `F_OK`, `X_OK` | find_command.c, bonus/parse/find_command.c | `F_OK` dosyanın varlığını, `X_OK` yürütme iznini kontrol eder. |
| **Standart dosya tanımlayıcıları** *(unistd.h)* | `STDIN_FILENO`, `STDOUT_FILENO` | child_utils.c, here_doc.c | Standart giriş/çıkış dosya tanımlayıcılarını (0 ve 1) temsil eder. |
| **errno sabitleri** *(errno.h)* | `EACCES`, `EINTR` | child_utils.c, process_manager.c, bonus/pipex_utils/child_utils.c, bonus/pipex_utils/process_manager.c, file_utils.c | Hata türlerini belirtir: `EACCES` — izin hatası, `EINTR` — sistem çağrısı kesintiye uğradı. |
| **wait durum makroları** *(sys/wait.h)* | `WIFEXITED`, `WEXITSTATUS`, `WIFSIGNALED`, `WTERMSIG` | process_manager.c, bonus/pipex_utils/process_manager.c | `waitpid`’in döndürdüğü `status` değerini çözümleyerek çocuğun çıkış durumunu analiz eder. |
| **NULL** *(stdlib.h / stddef.h)* | `NULL` | Genel kullanım (birçok dosya) | Boş işaretçi göstergesi. |
| **EXIT_FAILURE** *(stdlib.h)* | `EXIT_FAILURE` | main.c, here_doc.c, initialize fonksiyonları | Programın başarısızlıkla sonlandırılması için standart dönüş değeri. |

---

> 📘 **Not:** Bu tablo hem *mandatory* hem de *bonus* bölümlerindeki makroları tek bir yerde toplar.