#ifndef BOOK_MANAGER_H
#define BOOK_MANAGER_H

#include <vector>
#include <memory>
#include <algorithm>
#include "Book.h"

class BookManager {
private:
    std::vector<Book> books;  // 存储所有图书

public:
    // 添加图书
    void addBook(const Book& book);
    
    // 根据ISBN删除图书
    bool removeBook(const std::string& isbn);
    
    // 根据ISBN查找图书
    Book* findBook(const std::string& isbn);
    
    // 获取所有图书
    const std::vector<Book>& getAllBooks() const;
    
    // 根据不同条件查找图书
    std::vector<Book> findBooksByTitle(const std::string& title);
    std::vector<Book> findBooksByAuthor(const std::string& author);
    
    // 获取图书总数
    size_t getBookCount() const;
};

#endif // BOOK_MANAGER_H