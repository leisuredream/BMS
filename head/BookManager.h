#ifndef BOOK_MANAGER_H
#define BOOK_MANAGER_H

#include <vector>
#include <memory>
#include <algorithm>
#include "Book.h"

// 添加排序规则枚举
enum class SortBy
{
    TITLE,
    AUTHOR,
    PUBLISHER,
    YEAR
};

enum class SortOrder
{
    ASCENDING,
    DESCENDING
};

class BookManager
{
private:
    std::vector<Book> books; // 存储所有图书
    // 添加私有排序辅助方法
    void sortBooks(std::vector<Book> &bookList, SortBy sortBy, SortOrder order) const;

public:
    // 添加图书
    void addBook(const Book &book);

    // 根据ISBN删除图书
    bool removeBook(const std::string &isbn);

    // 根据ISBN查找图书
    Book *findBookByIsbn(const std::string &isbn);

    // 获取所有图书
    const std::vector<Book> &getAllBooks() const;

    // 根据不同条件查找图书
    std::vector<Book> findBooksByTitle(const std::string &title);
    std::vector<Book> findBooksByAuthor(const std::string &author);
    std::vector<Book> findBooksByPublisher(const std::string &publisher);
    std::vector<Book> findBooksByYear(int year);
    std::vector<Book> findBooksByYearRange(int startYear, int endYear);

    // 添加新的排序方法
    std::vector<Book> getSortedBooks(SortBy sortBy, SortOrder order = SortOrder::ASCENDING) const;

    // 对搜索结果进行排序的方法
    std::vector<Book> sortSearchResults(const std::vector<Book> &searchResults,
                                        SortBy sortBy,
                                        SortOrder order = SortOrder::ASCENDING) const;

    // 获取图书总数
    size_t getBookCount() const;
};

#endif // BOOK_MANAGER_H