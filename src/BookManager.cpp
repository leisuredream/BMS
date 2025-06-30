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

Book* BookManager::findBook(const std::string& isbn) {
    auto it = std::find_if(books.begin(), books.end(),
        [&isbn](const Book& book) { return book.getIsbn() == isbn; });
    
    return (it != books.end()) ? &(*it) : nullptr;
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