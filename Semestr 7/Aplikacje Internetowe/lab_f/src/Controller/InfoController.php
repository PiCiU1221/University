<?php
namespace App\Controller;

class InfoController
{
    public function infoAction(): ?string
    {
        ob_start();
        phpinfo();
        $html = ob_get_clean();
        return $html;
    }
}
