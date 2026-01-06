<?php
require_once __DIR__ . DIRECTORY_SEPARATOR . '..' . DIRECTORY_SEPARATOR . 'autoload.php';

$config = new \App\Service\Config();

$templating = new \App\Service\Templating();
$router = new \App\Service\Router();

$action = $_REQUEST['action'] ?? null;
switch ($action) {
    case 'book-index':
    case null:
        $controller = new \App\Controller\BookController();
        $view = $controller->indexAction($templating, $router);
        break;

    case 'book-create':
        $controller = new \App\Controller\BookController();
        $view = $controller->createAction($_REQUEST['book'] ?? null, $templating, $router);
        break;

    case 'book-edit':
        if (! $_REQUEST['id']) {
            break;
        }
        $controller = new \App\Controller\BookController();
        $view = $controller->editAction($_REQUEST['id'], $_REQUEST['book'] ?? null, $templating, $router);
        break;

    case 'book-show':
        if (! $_REQUEST['id']) {
            break;
        }
        $controller = new \App\Controller\BookController();
        $view = $controller->showAction($_REQUEST['id'], $templating, $router);
        break;

    case 'book-delete':
        if (! $_REQUEST['id']) {
            break;
        }
        $controller = new \App\Controller\BookController();
        $view = $controller->deleteAction($_REQUEST['id'], $router);
        break;

    case 'info':
        $controller = new \App\Controller\InfoController();
        $view = $controller->infoAction();
        break;

    default:
        $view = 'Not found';
        break;
}

if ($view) {
    echo $view;
}
