#include "../head/BookManager.h"
#include <iterator>

void BookManager::addBook(const Book& book) {
    books.push_back(book);
}

bool BookManager::removeBook(const std::string& isbn) {
    auto it = std::find_if(books.begin(), books.end(),
        [&isbn](const Book& book) { return book.getIsbn() == isbn; });
    
    if (it != books.end()) {
        books.erase(it);
        return true;
    }
    return false;
}

Book* BookManager::findBookByIsbn(const std::string& isbn) {
    auto it = std::find_if(books.begin(), books.end(),
        [&isbn](const Book& book) { return book.getIsbn() == isbn; });
    
    return (it != books.end()) ? &(*it) : nullptr;
}
std::vector<Book> BookManager::findBooksByPublisher(const std::string& publisher) {
    std::vector<Book> result;
    std::copy_if(books.begin(), books.end(), std::back_inserter(result),
        [&publisher](const Book& book) { return book.getPublisher() == publisher; });
    return result;
}

std::vector<Book> BookManager::findBooksByYear(int year) {
    std::vector<Book> result;
    std::copy_if(books.begin(), books.end(), std::back_inserter(result),
        [year](const Book& book) { return book.getPublishYear() == year; });
    return result;
}

std::vector<Book> BookManager::findBooksByYearRange(int startYear, int endYear) {
    std::vector<Book> result;
    std::copy_if(books.begin(), books.end(), std::back_inserter(result),
        [startYear, endYear](const Book& book) {
            int year = book.getPublishYear();
            return year >= startYear && year <= endYear;
        });
    return result;
}

const std::vector<Book>& BookManager::getAllBooks() const {
    return books;
}

std::vector<Book> BookManager::findBooksByTitle(const std::string& title) {
    std::vector<Book> result;
    std::copy_if(books.begin(), books.end(), std::back_inserter(result),
        [&title](const Book& book) { return book.getTitle() == title; });
    return result;
}

std::vector<Book> BookManager::findBooksByAuthor(const std::string& author) {
    std::vector<Book> result;
    std::copy_if(books.begin(), books.end(), std::back_inserter(result),
        [&author](const Book& book) { return book.getAuthor() == author; });
    return result;
}

size_t BookManager::getBookCount() const {
    return books.size();
}

// 实现排序方法
void BookManager::sortBooks(std::vector<Book>& bookList, SortBy sortBy, SortOrder order) const {
    auto comparator = [sortBy](const Book& a, const Book& b) {
        switch (sortBy) {
            case SortBy::TITLE:
                return a.getTitle() < b.getTitle();
            case SortBy::AUTHOR:
                return a.getAuthor() < b.getAuthor();
            case SortBy::PUBLISHER:
                return a.getPublisher() < b.getPublisher();
            case SortBy::YEAR:
                return a.getPublishYear() < b.getPublishYear();
            default:
                return false;
        }
    };

    if (order == SortOrder::ASCENDING) {
        std::sort(bookList.begin(), bookList.end(), comparator);
    } else {
        std::sort(bookList.begin(), bookList.end(), 
            [&comparator](const Book& a, const Book& b) { return !comparator(a, b); });
    }
}

std::vector<Book> BookManager::getSortedBooks(SortBy sortBy, SortOrder order) const {
    std::vector<Book> sortedBooks = books;
    sortBooks(sortedBooks, sortBy, order);
    return sortedBooks;
}

std::vector<Book> BookManager::sortSearchResults(const std::vector<Book>& searchResults, 
                                               SortBy sortBy, 
                                               SortOrder order) const {
    std::vector<Book> sortedResults = searchResults;
    sortBooks(sortedResults, sortBy, order);
    return sortedResults;
}