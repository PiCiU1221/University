<?php
/** @var $book ?\App\Model\Book */
?>

<div class="form-group">
    <label for="title">Title</label>
    <input type="text" id="title" name="book[title]" value="<?= $book ? $book->getTitle() : '' ?>">
</div>

<div class="form-group">
    <label for="author">Author</label>
    <input type="text" id="author" name="book[author]" value="<?= $book ? $book->getAuthor() : '' ?>">
</div>

<div class="form-group">
    <label for="published_year">Published Year</label>
    <input type="text" id="published_year" name="book[published_year]" value="<?= $book ? $book->getPublishedYear() : '' ?>">
</div>

<div class="form-group">
    <label for="genre">Genre</label>
    <input type="text" id="genre" name="book[genre]" value="<?= $book ? $book->getGenre() : '' ?>">
</div>

<div class="form-group">
    <label for="isbn">ISBN</label>
    <input type="text" id="isbn" name="book[isbn]" value="<?= $book ? $book->getIsbn() : '' ?>">
</div>

<div class="form-group">
    <input type="submit" value="Submit">
</div>
