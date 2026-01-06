<?php
/** @var \App\Model\Book $book */
/** @var \App\Service\Router $router */

$title = 'Create Book';
$bodyClass = "edit";

ob_start(); ?>
    <h1>Create Book</h1>
    <form action="<?= $router->generatePath('book-create') ?>" method="post" class="edit-form">
        <?php require __DIR__ . DIRECTORY_SEPARATOR . '_form.html.php'; ?>
        <input type="hidden" name="action" value="book-create">
    </form>

    <a href="<?= $router->generatePath('book-index') ?>">Back to list</a>
<?php $main = ob_get_clean();

include __DIR__ . DIRECTORY_SEPARATOR . '..' . DIRECTORY_SEPARATOR . 'base.html.php';
