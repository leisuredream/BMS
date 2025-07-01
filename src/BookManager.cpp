#include "../head/BookManager.h"
#include <iterator>
#include "../head/Mysort.h"

void BookManager::addBook(const Book& book) {
    books.push_back(book);
}

bool BookManager::removeBook(const std::string& isbn) {
    // 定义获取ISBN的函数
    auto getIsbn = [](const Book& book) -> std::string { 
        return book.getIsbn(); 
    };
    
    // 定义比较函数
    auto comp = [](const std::string& a, const std::string& b) { 
        return a < b; 
    };
    
    // 使用二分查找找到图书位置
    int index = books.binarySearch(isbn, getIsbn, comp);
    
    if (index >= 0) {
        books.removeAt(index);
        return true;
    }
    return false;
}

Book* BookManager::findBookByIsbn(const std::string& isbn) {
    // 定义获取键值的函数
    auto getIsbn = [](const Book& book) -> std::string { 
        return book.getIsbn(); 
    };
    
    // 定义比较函数
    auto comp = [](const std::string& a, const std::string& b) { 
        return a < b; 
    };
    
    int index = books.binarySearch(isbn, getIsbn, comp);
    return index >= 0 ? &books[index] : nullptr;
}

MyVector<Book> BookManager::findBooksByPublisher(const std::string& publisher) {
    MyVector<Book> result;
    auto getPublisher = [](const Book& book) -> std::string { 
        return book.getPublisher(); 
    };
    
    auto comp = [](const std::string& a, const std::string& b) { 
        return a < b; 
    };
    
    int index = books.binarySearch(publisher, getPublisher, comp);
    if (index >= 0) {
        // 向两边扩展查找所有相同出版社的图书
        int left = index, right = index;
        while (left >= 0 && books[left].getPublisher() == publisher) {
            result.push_back(books[left]);
            --left;
        }
        while (right < books.getSize() && books[right].getPublisher() == publisher) {
            if (right > index) {  // 避免重复添加index位置的元素
                result.push_back(books[right]);
            }
            ++right;
        }
    }
    return result;
}

MyVector<Book> BookManager::findBooksByYear(int year) {
    MyVector<Book> result;
    auto getYear = [](const Book& book) -> int { 
        return book.getPublishYear(); 
    };
    
    auto comp = [](const int a, const int b) { 
        return a < b; 
    };
    
    int index = books.binarySearch(year, getYear, comp);
    if (index >= 0) {
        // 向两边扩展查找所有相同年份的图书
        int left = index, right = index;
        while (left >= 0 && books[left].getPublishYear() == year) {
            result.push_back(books[left]);
            --left;
        }
        while (right < books.getSize() && books[right].getPublishYear() == year) {
            if (right > index) {
                result.push_back(books[right]);
            }
            ++right;
        }
    }
    return result;
}

MyVector<Book> BookManager::findBooksByYearRange(int startYear, int endYear) {
    MyVector<Book> result;
    
    // 定义获取年份的函数
    auto getYear = [](const Book& book) -> int {
        return book.getPublishYear();
    };
    
    // 定义比较函数
    auto comp = [](const int a, const int b) {
        return a < b;
    };
    
    // 查找起始年份的位置
    int startIndex = books.binarySearch(startYear, getYear, comp);
    if (startIndex < 0) {
        startIndex = 0;  // 如果找不到精确匹配，从0开始
    }
    
    // 从起始位置开始收集符合条件的图书
    for (int i = startIndex; i < books.getSize(); ++i) {
        int year = books[i].getPublishYear();
        if (year > endYear) break;  // 超出范围则停止
        if (year >= startYear) {
            result.push_back(books[i]);
        }
    }
    
    return result;
}

const MyVector<Book>& BookManager::getAllBooks() const {
    return books;
}

MyVector<Book> BookManager::findBooksByTitle(const std::string& title) {
    MyVector<Book> result;
    
    // 定义获取标题的函数
    auto getTitle = [](const Book& book) -> std::string {
        return book.getTitle();
    };
    
    // 定义比较函数
    auto comp = [](const std::string& a, const std::string& b) {
        return a < b;
    };
    
    // 使用二分查找找到匹配的书籍
    int index = books.binarySearch(title, getTitle, comp);
    if (index >= 0) {
        // 向两边扩展查找所有相同标题的图书
        int left = index, right = index;
        while (left >= 0 && books[left].getTitle() == title) {
            result.push_back(books[left]);
            --left;
        }
        while (right < books.getSize() && books[right].getTitle() == title) {
            if (right > index) {
                result.push_back(books[right]);
            }
            ++right;
        }
    }
    return result;
}

MyVector<Book> BookManager::findBooksByAuthor(const std::string& author) {
    MyVector<Book> result;
    
    // 定义获取作者的函数
    auto getAuthor = [](const Book& book) -> std::string {
        return book.getAuthor();
    };
    
    // 定义比较函数
    auto comp = [](const std::string& a, const std::string& b) {
        return a < b;
    };
    
    // 使用二分查找找到匹配的书籍
    int index = books.binarySearch(author, getAuthor, comp);
    if (index >= 0) {
        // 向两边扩展查找所有相同作者的图书
        int left = index, right = index;
        while (left >= 0 && books[left].getAuthor() == author) {
            result.push_back(books[left]);
            --left;
        }
        while (right < books.getSize() && books[right].getAuthor() == author) {
            if (right > index) {
                result.push_back(books[right]);
            }
            ++right;
        }
    }
    return result;
}

size_t BookManager::getBookCount() const {
    return books.getSize();
}

// 添加静态比较函数
static bool compareBooks(const Book& a, const Book& b, SortBy sortBy, SortOrder order) {
    bool result;
    switch (sortBy) {
        case SortBy::TITLE:
            result = a.getTitle() < b.getTitle();
            break;
        case SortBy::AUTHOR:
            result = a.getAuthor() < b.getAuthor();
            break;
        case SortBy::PUBLISHER:
            result = a.getPublisher() < b.getPublisher();
            break;
        case SortBy::YEAR:
            result = a.getPublishYear() < b.getPublishYear();
            break;
        default:
            result = false;
    }
    return order == SortOrder::ASCENDING ? result : !result;
}

void BookManager::sortBooks(MyVector<Book>& bookList, SortBy sortBy, SortOrder order) const {
    size_t length = bookList.getSize();
    if (length <= 1) return;

    Book* arr = new Book[length];
    for (size_t i = 0; i < length; ++i) {
        arr[i] = bookList[i];
    }

    // 使用静态比较函数
    auto comp = [sortBy, order](const Book& a, const Book& b) -> bool {
        return compareBooks(a, b, sortBy, order);
    };
    
    MyAlgorithm::sort(arr, length, comp);

    for (size_t i = 0; i < length; ++i) {
        bookList[i] = arr[i];
    }

    delete[] arr;
}

MyVector<Book> BookManager::getSortedBooks(SortBy sortBy, SortOrder order) const {
    MyVector<Book> sortedBooks = books;
    sortBooks(sortedBooks, sortBy, order);
    return sortedBooks;
}

MyVector<Book> BookManager::sortSearchResults(const MyVector<Book>& searchResults, 
                                               SortBy sortBy, 
                                               SortOrder order) const {
    MyVector<Book> sortedResults = searchResults;
    sortBooks(sortedResults, sortBy, order);
    return sortedResults;
}