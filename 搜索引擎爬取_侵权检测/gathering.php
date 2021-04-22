<?php
header("Content-type: text/html; charset=utf-8");
error_reporting(1);
set_time_limit(6000);
ini_set('pcre.backtrack_limit', 10000000);

function getSogouContent($url){
        $ch =curl_init();
        curl_setopt($ch,CURLOPT_URL,$url);

        $header = array();
        $header[] = "Accept:text/html,application/xhtml+xml,application/xml;q=0.9,image/webp,*/*;q=0.8";
        $header[] = "Accept-Language:zh-CN,zh;q=0.8";
        $header[] = "User-Agent:Mozilla/5.0 (Windows NT 6.1) AppleWebKit/537.36 (KHTML, like Gecko) Chrome/56.0.2924.87 Safari/537.36";

        curl_setopt($ch,CURLOPT_RETURNTRANSFER,true);
        curl_setopt($ch,CURLOPT_HEADER,false);
        curl_setopt($ch,CURLOPT_HTTPHEADER,$header);

        $content = curl_exec($ch);

        return $content;
}

function getBaiduContent($url){
    $ch =curl_init();
    curl_setopt($ch,CURLOPT_URL,$url);

    $header = array();
    $header[] = "Connection: keep-alive";
    $header[] = "Cache-Control: max-age=0";
    $header[] = "DNT: 1";
    $header[] = "Upgrade-Insecure-Requests: 1";
    $header[] = "User-Agent: Mozilla/5.0 (Macintosh; Intel Mac OS X 10_15_4) AppleWebKit/537.36 (KHTML, like Gecko) Chrome/81.0.4044.129 Safari/537.36";
    $header[] = "Accept: text/html,application/xhtml+xml,application/xml;q=0.9,image/webp,image/apng,*/*;q=0.8,application/signed-exchange;v=b3;q=0.9";
    $header[] = "Sec-Fetch-Site: same-origin";
    $header[] = "Sec-Fetch-Mode: navigate";
    $header[] = "Sec-Fetch-User: ?1";
    $header[] = "Sec-Fetch-Dest: document";
    $header[] = "Referer: https://www.baidu.com/?tn=simple";
    $header[] = "Accept-Language: zh-CN,zh;q=0.9,en;q=0.8,fr;q=0.7";

    curl_setopt($ch,CURLOPT_RETURNTRANSFER,true);
    curl_setopt($ch,CURLOPT_HEADER,false);
    curl_setopt($ch,CURLOPT_HTTPHEADER,$header);

    $content = curl_exec($ch);

    return $content;
}

if (! empty($_POST)) {
    $platform = $_POST['platform'];
    $select = $_POST['select'];
    $blacklist = $_POST['blacklist'];
    $blacktitle = $_POST['blacktitle'];
    $merge = $_POST['merge'];
    $article = $_POST['article'];
    $blacklists = explode('|', $blacklist);
    $blacktitles = explode('|', $blacktitle);
    
    $sheets = array();
    $total = 1;
    if ($platform == 1) {
        foreach ($select as $val) {
            for ($i = 0; $i < $val['page']; $i ++) {
                $data = '';
                $nowpage = $i * 10;
                // $fp = @fsockopen('www.baidu.com', 80, $errno, $errstr, 20);
                // @fputs($fp, "GET /s?wd=" . urlencode($val['query']) . "&pn=" . $nowpage . "  HTTP/1.1\r\nHost:www.baidu.com\r\nConnection: Close\r\n\r\n");
                // while ($fp && ! feof($fp)) {
                //     $data .= fread($fp, 1024);
                // }
                // @fclose($fp);
                
                $data = getBaiduContent("https://www.baidu.com/s?pn=1&wd=". urlencode($val['query']). "&pn=" . $nowpage  );
                // $myfile = fopen("data.txt", "w") or die("Unable to open file!");
                // fwrite($myfile, $data);

                // 获取含有URL链接的div
                $data = preg_replace("/[\t\n\r]+/", "", $data);
                preg_match_all("/<h3 class=\"t\"(.*)<\/h3>/iU", $data, $exps);
                // 根据URL进一步获取真实的URL
                $urls = array();
                $keywords = array();
                foreach ($exps[1] as $exp) {
                    // 如果标题包含关键字，则获取真实地址
                    preg_match("/<a (.*)>(.*)<\/a>/iU", $exp, $exp1);
                    $flag = true;
                    $contains = explode('|', $val['required_query']);
                    foreach ($contains as $contain) {
                        if (strpos($exp1[2], trim($contain)) === false) {
                            $flag = false;
                            break;
                        }
                    }
                    foreach ($blacktitles as $title) {
                        if (strpos($exp1[2], trim($title)) !== false) {
                            $flag = false;
                            break;
                        }
                    }
                    if ($flag) {
                        preg_match_all('/href\s*=\s*(?:"([^"]*)"|\'([^\']*)\'|([^"\'>\s]+))/is', $exp, $match);
                        $info = parse_url($match[1][0]);
                        // 取得真实URL
                        $fp = fsockopen($info['host'], 80, $errno, $errstr, 30);
                        fputs($fp, "GET {$info['path']}?{$info['query']} HTTP/1.1\r\n");
                        fputs($fp, "Host: {$info['host']}\r\n");
                        fputs($fp, "Connection: close\r\n\r\n");
                        $rewrite = '';
                        while (! feof($fp)) {
                            $line = fgets($fp);
                            if ($line != "\r\n") {
                                if (strpos($line, 'Location:') !== false) {
                                    $rewrite = str_replace(array(
                                        "\r",
                                        "\n",
                                        "Location: "
                                    ), '', $line);
                                    $flag1 = true;
                                    foreach ($blacklists as $black) {
                                        if (strpos($rewrite, trim($black)) !== false) {
                                            $flag1 = false;
                                            break;
                                        }
                                    }
                                    
                                    if ($flag1) {
                                        $keywords[] = $exp1[2];
                                        $url = rtrim(trim($rewrite),'&quot;');
                                        if(!preg_match("/([a-z0-9][a-z0-9\-]*?\.(?:com|cn|net|org|gov|info|la|cc|co)(?:\.(?:cn|jp))?\/?)$/", $url)){
                                                $urls[] = $url;
                                        }
                                    }
                                }
                            } else {
                                break;
                            }
                        }
                    }
                }
                if (! empty($urls)) {
                    $sheets[$total]['query'] = "https://www.baidu.com/s?wd=" . urlencode($val['query']) . "&pn=" . $nowpage;
                    $sheets[$total]['urls'] = $urls;
                    $sheets[$total]['keywords'] = $keywords;
                    $total ++;
                }
            }
        }
    } else 
        if ($platform == 2) {
            foreach ($select as $val) {
                for ($i = 0; $i < $val['page']; $i ++) {
                    $data = '';
                    $result_url = 'https://www.so.com/s?q=' . urlencode($val['query']) . '&pn=' . ($i + 1);
                    $data = file_get_contents($result_url);
                    // 获取含有URL链接的div
                    $data = preg_replace("/[\t\n\r]+/", "", $data);

                    // $myfile = fopen("data.txt", "w") or die("Unable to open file!");
                    // fwrite($myfile, $data);
                    
                    preg_match_all("/<h3  class=\"res-title\">(.*)<\/h3>/iU", $data, $exps1);
                    preg_match_all("/<h3 class=\"res-title \">(.*)<\/h3>/iU", $data, $exps2);

                    preg_match_all("/<li class=\"res-list\">(.*)<\/h3>/iU", $data, $tttt);
                    // $myfile = fopen("tttt.txt", "w") or die("Unable to open file!");
                    // fwrite($myfile, $tttt);

                    $urls_tmp = array_merge($exps1[1], $exps2[1]);

                    // $myfile = fopen("urls_tmp.txt", "w") or die("Unable to open file!");
                    // fwrite($myfile, $urls_tmp);

                     //print_r($urls_tmp);die;
                    if (! empty($urls_tmp)) {
                        $urls = array();
                        $keywords = array();
                        foreach ($urls_tmp as $url) {
                            preg_match("/<a (.*)data-mdurl=\"(.*)\"(.*)>(.*)<\/a>/iU", $url, $exp);
                            //print_r($exp);die;
                            $flag = true;
                            $contains = explode('|', $val['required_query']);
                            foreach ($contains as $contain) {
                                if (strpos($exp[4], trim($contain)) === false) {
                                    $flag = false;
                                }
                            }
                            foreach ($blacktitles as $title) {
                                if (strpos($exp[4], trim($title)) !== false) {
                                    $flag = false;
                                    break;
                                }
                            }
                            if ($flag) {
                               // $url = parse_url($url);
                               // $exp3 = explode('&', $url['query']);
                                $url = $exp[2];
                                $flag1 = true;
                                foreach ($blacklists as $black) {
                                    if (strpos($url, trim($black)) !== false) {
                                        $flag1 = false;
                                        break;
                                    }
                                }
                                
                                if ($flag1) {
                                    $keywords[] = $exp[4];
                                        if(!preg_match("/([a-z0-9][a-z0-9\-]*?\.(?:com|cn|net|org|gov|info|la|cc|co)(?:\.(?:cn|jp))?\/?)$/", $url)){
                                                $urls[] = $url;
                                        }
                                }
                            }
                        }
                    }
                    // print_r($urls);
                    if (! empty($urls)) {
                        $sheets[$total]['query'] = $result_url;
                        $sheets[$total]['urls'] = $urls;
                        $sheets[$total]['keywords'] = $keywords;
                        $total ++;
                    }
                }
            }
        } else 
            if ($platform == 3) {
                foreach ($select as $val) {
					sleep(5);
                    for ($i = 0; $i < $val['page']; $i ++) {
                        $data = '';
                        $result_url = 'http://www.sogou.com/web?query=' . urlencode($val['query']) . '&page=' . ($i + 1);
                        $data = getSogouContent($result_url);
                       // print_r($data);die;
                        // 获取含有URL链接的div
                        $data = preg_replace("/[\t\n\r]+/", "", $data);

                        preg_match_all("/<h3 class=\"pt\"(.*)<\/h3>/iU", $data, $exps1);
                        preg_match_all("/<h3 class=\"vrTitle\"(.*)<\/h3>/iU", $data, $exps2);
                        $urls_tmp = array_merge($exps1[1], $exps2[1]);
                        // print_r($urls_tmp);
                        if (! empty($urls_tmp)) {
                            $urls = array();
                            $keywords = array();
                            foreach ($urls_tmp as $url) {
                                preg_match("/<a (.*)>(.*)<\/a>/iU", $url, $exp);
                                $flag = true;
                                $contains = explode('|', $val['required_query']);
                                foreach ($contains as $contain) {
                                    if (strpos($exp[2], trim($contain)) === false) {
                                        $flag = false;
                                    }
                                }
                                foreach ($blacktitles as $title) {
                                    if (strpos($exp[2], trim($title)) !== false) {
                                        $flag = false;
                                        break;
                                    }
                                }
                                if ($flag) {
                                    preg_match_all('/href\s*=\s*(?:"([^"]*)"|\'([^\']*)\'|([^"\'>\s]+))/is', $url, $match);
                                    $url = $match[1][0];
                                    $flag1 = true;
                                    foreach ($blacklists as $black) {
                                        if (strpos($url, trim($black)) !== false) {
                                            $flag1 = false;
                                            break;
                                        }
                                    }
                                    
                                    if ($flag1) {
                                        $keywords[] = $exp[2];
                                        if(!preg_match("/([a-z0-9][a-z0-9\-]*?\.(?:com|cn|net|org|gov|info|la|cc|co)(?:\.(?:cn|jp))?\/?)$/", $url)){
                                                $urls[] = $url;
                                        }
                                    }
                                }
                            }
                        }
                        // print_r($urls);
                        if (! empty($urls)) {
                            $sheets[$total]['query'] = $result_url;
                            $sheets[$total]['urls'] = $urls;
                            $sheets[$total]['keywords'] = $keywords;
                            $total ++;
                        }
                    }
                }
            } else 
            if ($platform == 4) {
                foreach ($select as $val) {
                    for ($i = 0; $i < $val['page']; $i ++) {
                        $data = '';
                        //$result_url = 'http://m.sm.cn/s?q=' . urlencode($val['query']) . '&page=' . ($i + 1);
                        $result_url = 'https://cn.bing.com/search?&q=' . urlencode($val['query']) . '&first=' . ($i + 1)*10;
                        $data = file_get_contents($result_url);
                        // 获取含有URL链接的div
                        $data = preg_replace("/[\t\n\r]+/", "", $data);
                        // $myfile = fopen("data.txt", "w") or die("Unable to open file!");
                        // fwrite($myfile, $data);
                        
                        //preg_match_all("/<div class=\"article ali_row\">(.*)<\/div>/iU", $data, $exps);       
                        preg_match_all("/<h2>(.*)<\/h2>/iU", $data, $exps);       
                        
                        // $myfile = fopen("exps.txt", "w") or die("Unable to open file!");
                        // fwrite($myfile, $exps);
                        // print_r($exps);die;
                        if (! empty($exps[0])) {
                            $urls = array();
                            $keywords = array();
                            foreach ($exps[0] as $url) {
                                preg_match("/<h2>(.*)<\/h2>/iU", $url, $exp);
                                $flag = true;
                                $contains = explode('|', $val['required_query']);
                                $new_title = strip_tags($exp[0]);
                                
                                foreach ($contains as $contain) {
                                    if (strpos($new_title, trim($contain)) === false) {
                                        $flag = false;
                                    }
                                }
                                foreach ($blacktitles as $title) {
                                    if (strpos($new_title, trim($title)) !== false) {
                                        $flag = false;
                                        break;
                                    }
                                }
                                if ($flag) {
                                    preg_match_all('/<h2><a target=\"_blank\" href\s*=\s*(?:"([^"]*)"|\'([^\']*)\'|([^"\'>\s]+))/is', $url, $match);
                                    $url = $match[1][0];
                                    $flag1 = true;
                                    foreach ($blacklists as $black) {
                                        if (strpos($url, trim($black)) !== false) {
                                            $flag1 = false;
                                            break;
                                        }
                                    }
                                    
                                    if ($flag1) {
                                        $keywords[] = $new_title;
                                        if(!preg_match("/([a-z0-9][a-z0-9\-]*?\.(?:com|cn|net|org|gov|info|la|cc|co)(?:\.(?:cn|jp))?\/?)$/", $url)){
                                                $urls[] = $url;
                                        }
                                    }
                                }
                            }
                        }
                        // print_r($urls);
                        if (! empty($urls)) {
                            $sheets[$total]['query'] = $result_url;
                            $sheets[$total]['urls'] = $urls;
                            $sheets[$total]['keywords'] = $keywords;
                            $total ++;
                        }
                    }
                }
            }
    // print_r($sheets);die;
    
    /**
     * ***************************************************导出excel***************************************************
     */
    require_once 'PHPExcel/Classes/PHPExcel.php';
    require_once 'PHPExcel/Classes/PHPExcel/IOFactory.php';
    $objPHPExcel = new PHPExcel();
    /* 设置单元格的标题 */
    $objPHPExcel->setActiveSheetIndex(0)->mergeCells('A1:F1'); // 合并单元格
    $objPHPExcel->setActiveSheetIndex(0)->setCellValue('A1', '侵权监测结果');
    // 设置font
    $objPHPExcel->setActiveSheetIndex(0)
        ->getStyle('A1')
        ->getFont()
        ->setSize(14);
    $objPHPExcel->setActiveSheetIndex(0)
        ->getStyle('A1')
        ->getFont()
        ->setBold(true);
    $objPHPExcel->setActiveSheetIndex(0)
        ->getStyle('A1')
        ->getFont()
        ->getColor()
        ->setARGB(PHPExcel_Style_Color::COLOR_BLACK);
    // 水平居中===垂直居中
    $objPHPExcel->setActiveSheetIndex(0)
        ->getStyle('A1')
        ->getAlignment()
        ->setHorizontal(PHPExcel_Style_Alignment::HORIZONTAL_CENTER);
    $objPHPExcel->setActiveSheetIndex(0)
        ->getStyle('A1')
        ->getAlignment()
        ->setVertical(PHPExcel_Style_Alignment::VERTICAL_CENTER);
    
    /* 设置特别表格的宽度 */
    $objPHPExcel->setActiveSheetIndex(0)
        ->getColumnDimension('A')
        ->setWidth(15); // 表示设置A这一列的宽度,以下一样
    $objPHPExcel->setActiveSheetIndex(0)
        ->getColumnDimension('B')
        ->setWidth(10);
    $objPHPExcel->setActiveSheetIndex(0)
        ->getColumnDimension('C')
        ->setWidth(50);
    $objPHPExcel->setActiveSheetIndex(0)
        ->getColumnDimension('D')
        ->setWidth(10);
    $objPHPExcel->setActiveSheetIndex(0)
        ->getColumnDimension('E')
        ->setWidth(10);
    $objPHPExcel->setActiveSheetIndex(0)
        ->getColumnDimension('F')
        ->setWidth(60);
    
    $objPHPExcel->setActiveSheetIndex(0)->setCellValue('A2', '作品名称');
    $objPHPExcel->setActiveSheetIndex(0)->setCellValue('B2', '平台');
    $objPHPExcel->setActiveSheetIndex(0)->setCellValue('C2', '链接网址');
    $objPHPExcel->setActiveSheetIndex(0)->setCellValue('D2', '发函情况');
    $objPHPExcel->setActiveSheetIndex(0)->setCellValue('E2', '处理结果');
    $objPHPExcel->setActiveSheetIndex(0)->setCellValue('F2', '标题');
    
    // 设置font
    // 设置总的字体
    $objPHPExcel->setActiveSheetIndex(0)
        ->getStyle('A')
        ->getFont()
        ->setSize(10);
    $objPHPExcel->setActiveSheetIndex(0)
        ->getStyle('B')
        ->getFont()
        ->setSize(10);
    $objPHPExcel->setActiveSheetIndex(0)
        ->getStyle('C')
        ->getFont()
        ->setSize(10);
    $objPHPExcel->setActiveSheetIndex(0)
        ->getStyle('D')
        ->getFont()
        ->setSize(10);
    $objPHPExcel->setActiveSheetIndex(0)
        ->getStyle('E')
        ->getFont()
        ->setSize(10);
    $objPHPExcel->setActiveSheetIndex(0)
        ->getStyle('F')
        ->getFont()
        ->setSize(10);
    $objPHPExcel->setActiveSheetIndex(0)
        ->getStyle('G')
        ->getFont()
        ->setSize(10);
    // 设置第二行单行字体
    $objPHPExcel->setActiveSheetIndex(0)
        ->getStyle('A2')
        ->getFont()
        ->setSize(12);
    $objPHPExcel->setActiveSheetIndex(0)
        ->getStyle('A2')
        ->getFont()
        ->setBold(true);
    $objPHPExcel->setActiveSheetIndex(0)
        ->getStyle('A2')
        ->getFont()
        ->getColor()
        ->setARGB(PHPExcel_Style_Color::COLOR_BLACK);
    $objPHPExcel->setActiveSheetIndex(0)
        ->getStyle('B2')
        ->getFont()
        ->setSize(12);
    $objPHPExcel->setActiveSheetIndex(0)
        ->getStyle('B2')
        ->getFont()
        ->setBold(true);
    $objPHPExcel->setActiveSheetIndex(0)
        ->getStyle('B2')
        ->getFont()
        ->getColor()
        ->setARGB(PHPExcel_Style_Color::COLOR_BLACK);
    $objPHPExcel->setActiveSheetIndex(0)
        ->getStyle('C2')
        ->getFont()
        ->setSize(12);
    $objPHPExcel->setActiveSheetIndex(0)
        ->getStyle('C2')
        ->getFont()
        ->setBold(true);
    $objPHPExcel->setActiveSheetIndex(0)
        ->getStyle('C2')
        ->getFont()
        ->getColor()
        ->setARGB(PHPExcel_Style_Color::COLOR_BLACK);
    $objPHPExcel->setActiveSheetIndex(0)
        ->getStyle('D2')
        ->getFont()
        ->setSize(12);
    $objPHPExcel->setActiveSheetIndex(0)
        ->getStyle('D2')
        ->getFont()
        ->setBold(true);
    $objPHPExcel->setActiveSheetIndex(0)
        ->getStyle('D2')
        ->getFont()
        ->getColor()
        ->setARGB(PHPExcel_Style_Color::COLOR_BLACK);
    $objPHPExcel->setActiveSheetIndex(0)
        ->getStyle('E2')
        ->getFont()
        ->setSize(12);
    $objPHPExcel->setActiveSheetIndex(0)
        ->getStyle('E2')
        ->getFont()
        ->setBold(true);
    $objPHPExcel->setActiveSheetIndex(0)
        ->getStyle('E2')
        ->getFont()
        ->getColor()
        ->setARGB(PHPExcel_Style_Color::COLOR_BLACK);
    $objPHPExcel->setActiveSheetIndex(0)
        ->getStyle('F2')
        ->getFont()
        ->setSize(12);
    $objPHPExcel->setActiveSheetIndex(0)
        ->getStyle('F2')
        ->getFont()
        ->setBold(true);
    $objPHPExcel->setActiveSheetIndex(0)
        ->getStyle('F2')
        ->getFont()
        ->getColor()
        ->setARGB(PHPExcel_Style_Color::COLOR_BLACK);
    $objPHPExcel->setActiveSheetIndex(0)
        ->getStyle('G2')
        ->getFont()
        ->setBold(true);
    $objPHPExcel->setActiveSheetIndex(0)
        ->getStyle('G2')
        ->getFont()
        ->getColor()
        ->setARGB(PHPExcel_Style_Color::COLOR_BLACK);
    // 水平居中===垂直居中
    $objPHPExcel->setActiveSheetIndex(0)
        ->getStyle('A2')
        ->getAlignment()
        ->setHorizontal(PHPExcel_Style_Alignment::HORIZONTAL_CENTER);
    $objPHPExcel->setActiveSheetIndex(0)
        ->getStyle('A2')
        ->getAlignment()
        ->setVertical(PHPExcel_Style_Alignment::VERTICAL_CENTER);
    $objPHPExcel->setActiveSheetIndex(0)
        ->getStyle('B2')
        ->getAlignment()
        ->setHorizontal(PHPExcel_Style_Alignment::HORIZONTAL_CENTER);
    $objPHPExcel->setActiveSheetIndex(0)
        ->getStyle('B2')
        ->getAlignment()
        ->setVertical(PHPExcel_Style_Alignment::VERTICAL_CENTER);
    $objPHPExcel->setActiveSheetIndex(0)
        ->getStyle('C2')
        ->getAlignment()
        ->setHorizontal(PHPExcel_Style_Alignment::HORIZONTAL_CENTER);
    $objPHPExcel->setActiveSheetIndex(0)
        ->getStyle('C2')
        ->getAlignment()
        ->setVertical(PHPExcel_Style_Alignment::VERTICAL_CENTER);
    $objPHPExcel->setActiveSheetIndex(0)
        ->getStyle('D2')
        ->getAlignment()
        ->setHorizontal(PHPExcel_Style_Alignment::HORIZONTAL_CENTER);
    $objPHPExcel->setActiveSheetIndex(0)
        ->getStyle('D2')
        ->getAlignment()
        ->setVertical(PHPExcel_Style_Alignment::VERTICAL_CENTER);
    $objPHPExcel->setActiveSheetIndex(0)
        ->getStyle('E2')
        ->getAlignment()
        ->setHorizontal(PHPExcel_Style_Alignment::HORIZONTAL_CENTER);
    $objPHPExcel->setActiveSheetIndex(0)
        ->getStyle('E2')
        ->getAlignment()
        ->setVertical(PHPExcel_Style_Alignment::VERTICAL_CENTER);
    $objPHPExcel->setActiveSheetIndex(0)
        ->getStyle('F2')
        ->getAlignment()
        ->setHorizontal(PHPExcel_Style_Alignment::HORIZONTAL_CENTER);
    $objPHPExcel->setActiveSheetIndex(0)
        ->getStyle('F2')
        ->getAlignment()
        ->setVertical(PHPExcel_Style_Alignment::VERTICAL_CENTER);
    $objPHPExcel->setActiveSheetIndex(0)
        ->getStyle('G2')
        ->getAlignment()
        ->setHorizontal(PHPExcel_Style_Alignment::HORIZONTAL_CENTER);
    $objPHPExcel->setActiveSheetIndex(0)
        ->getStyle('G2')
        ->getAlignment()
        ->setVertical(PHPExcel_Style_Alignment::VERTICAL_CENTER);
    // 设置边框
    $styleArray = array(
        'borders' => array(
            'allborders' => array(
                // 'style' => PHPExcel_Style_Border::BORDER_THICK,//边框是粗的
                'style' => PHPExcel_Style_Border::BORDER_THIN
            ) // 细边框
                                                           // 'color' => array('argb' => 'FFFF0000'),
            
        )
    );
    $objPHPExcel->setActiveSheetIndex(0)
        ->getStyle('A2:F2')
        ->applyFromArray($styleArray);
    $platforms = array(
        1 => '百度搜索',
        2 => '360搜索',
        3 => '搜狗搜索',
        4 => '必应搜索'
    );
    if (! empty($sheets)) {
        $k = 3;
        foreach ($sheets as $sheet) {
            foreach ($sheet['urls'] as $index => $url) {
                $objPHPExcel->setActiveSheetIndex(0)->setCellValue('A' . $k, $article);
                $objPHPExcel->setActiveSheetIndex(0)->setCellValue('B' . $k, $platforms[$platform]);
                $objPHPExcel->setActiveSheetIndex(0)->setCellValue('C' . $k, $url);
                $objPHPExcel->setActiveSheetIndex(0)->setCellValue('D' . $k, date('Y-m-d'));
                $objPHPExcel->setActiveSheetIndex(0)->setCellValue('E' . $k, '待处理');
                $objPHPExcel->setActiveSheetIndex(0)->setCellValue('F' . $k, strip_tags($sheet['keywords'][$index]));
                
                $objPHPExcel->getActiveSheet()
                    ->getStyle('E' . $k)
                    ->getFill()
                    ->setFillType(PHPExcel_Style_Fill::FILL_SOLID);
                $objPHPExcel->getActiveSheet()
                    ->getStyle('E' . $k)
                    ->getFill()
                    ->getStartColor()
                    ->setARGB(PHPExcel_Style_Color::COLOR_YELLOW);
                
                $objPHPExcel->setActiveSheetIndex(0)
                    ->getStyle('A' . $k . ':F' . $k)
                    ->applyFromArray($styleArray);
                $k ++;
            }
        }
    }
    
    $objPHPExcel->getActiveSheet()->setTitle('搜索');
    $objPHPExcel->setActiveSheetIndex(0);
    $objWriter = PHPExcel_IOFactory::createWriter($objPHPExcel, 'Excel5');
    header("Content-Disposition:attachment;filename=" . date('y-m-d') . $article . '-' . $platforms[$platform] . " 侵权链接.xls");
    header("Content-Type:application/octet-stream");
    header("Content-Transfer-Encoding:binary");
    header("Pragma:no-cache");
    $objWriter->save('php://output');
    exit();
/**
 * ***************************************************导出excel结束***************************************************
 */
}
?>
<!DOCTYPE html>
<html>
<head>
<meta http-equiv="Content-Type" content="text/html;charset=UTF-8">
<title>四大搜索引擎侵权链接搜集系统</title>
<link rel="stylesheet" type="text/css"
	href="easyui/themes/default/easyui.css">
<link rel="stylesheet" type="text/css" href="easyui/themes/icon.css">
<script type="text/javascript" src="easyui/jquery.min.js"></script>
<script type="text/javascript" src="easyui/jquery.easyui.min.js"></script>
<script type="text/javascript" src="easyui/locale/easyui-lang-zh_CN.js"></script>
</head>
					<center>
						<div class="panel" style="width: 80%; margin: 0; font-size: 12px;">
	        			<table cellpadding="5" style="margin-top: 1px;">
	        	            <tr>
								<a>在线观看、迅雷下载、720p、1080p、吉吉影音、西瓜影音、蓝光版</a><br>
								<a style="color:red">网盘,云盘,百度云,下载,720,1080,BT,迅雷,影音,种子
在线,资源,西瓜影音，非凡影音，吉吉影音，先锋影音，快播
mp4，rmvb，hdtv，pan.baidu.com，yunpan.cn，torrent，电影网</a><br>
							</tr>

						</table>
					</center>
<body>

	<div style="margin-top: 10px;"></div>
	<center>
		<div class="easyui-panel" title="四大搜索引擎侵权链接搜集系统"
			style="width: 80%; margin: 0; font-size: 12px;">
			<div style="padding: 10px 30px 20px 30px">
				<form id="myform" method="post" action="">
					<table cellpadding="5">

						<tr class="query">
							<td>查询关键字：<input type="text" name="select[0][query]" size="30 "
								class="easyui-textbox" data-options="required:true" /></td>
							<td>标题必含关键字(多个关键字以|隔开)：<input type="text"
								name="select[0][required_query]" class="easyui-textbox"
								data-options="required:true" /></td>
							<td>查询页数：<input type="text" name="select[0][page]"
								class="easyui-textbox" data-options="required:true" /></td>
							<td><input type="button" value="新增" onclick="new_query()"></input></td>
						</tr>
						<tr>
							<td colSpan="4" style="vertical-align: top">作品名称:<input
								type="text" name="article" value="" size="30"
								class="easyui-textbox" data-options="required:true" />
							</td>
						</tr>
						<tr>
							<td colSpan="4" style="vertical-align: top">网址黑名单:<input
								type="text" name="blacklist"
								value="重点|baidu.com|iqiyi.com|qq.com|youku.com|tudou.com|le.com|letv.com|ifeng.com|sohu.com|56.com|sogou.com|baofeng.com|mgtv.com|sina.com.cn|fun.tvnews.163.com|douban.com||weibo.com|mtime.com|tvmao.com|音乐|ximalaya.com|yue365.com|music.163.com|xiami.com|kugou.com|kuwo.cn|新闻|51chuqi.com|people.com|游戏|pipaw.com|mobile-dad.com|37.com|资讯|zuocai.tv|baike.com|bjxyxd.com|1688.com|3158.cn|chinadaily.com.cn|xiumu.cn|256.cc|114la.com|pptv.com|1905.com"
								size="100" class="easyui-textbox" data-options="required:true" />
							</td>
						</tr>
						<tr>
							<td colSpan="4" style="vertical-align: top">标题黑名单:<input
								type="text" name="blacktitle"
								value="TXT|txt|小说|扮演|观后感|曲|片|什么|吗|台词|角色|发布会|,|!|:|，|：|？|？|?|?|#|。|手游|播出时间|周|畅销|娱乐八卦|明星|漫画|预告|哪|图|音乐|评|首款|公测|与|正式|人物|单机|壁纸|桌面|演员|将播|新闻|美颜|开|特效|收视率|吐槽|看点|电子书|曝光|多少|饰|破|这么|安卓|持续|在线阅读|定档|就|谁|亿|晚|黑客|遭|文字|素材|百科|上映时间|类似|确定|资讯|剧情分析|电影介绍|剧情介绍|今日|在线选座|特辑|精彩|提前|观影|点映|公映|真实|明日|引爆|口碑|票房|已经|标签|剧透|将是|剧情|预览|情节|剧情|简介|登陆|深圳热线|上映|高清剧照|玩转|恐怕"
								size="100" class="easyui-textbox" data-options="required:true" />
							</td>
						</tr>
						<tr>
							<td colSpan="4">是否合并单元格： <input type="radio" name="merge"
								value="1" checked="checked" />是 &nbsp;&nbsp; <input type="radio"
								name="merge" value="0" />否
							</td>
						</tr>
						<tr>
							<td colSpan="4">平台： <select name="platform"
								class="easyui-combobox" style="width: 60px;">
									<option value="1">百度</option>
									<option value="2">360</option>
									<option value="3">搜狗</option>
									<option value="4">必应</option>
							</select>
							</td>
						</tr>

					</table>
				</form>
				<div style="text-align: center; padding: 5px">
					<a href="javascript:void(0)" class="easyui-linkbutton"
						onclick="submitForm()">收&nbsp;&nbsp;集</a>
				</div>
			</div>
		</div>
	</center>
	<script>
    function new_query(){
        var query = $('table').find('.query');
       var  index = query.length;
       var str = '<tr class="query">'+
			'<td>查询关键字：<input  type="text" name="select['+index+'][query]"  size="30 " class="easyui-textbox"  data-options="required:true"/></td>'+
			'<td>标题必含关键字(多个关键字以|隔开)：<input  type="text" name="select['+index+'][required_query]"  class="easyui-textbox"  data-options="required:true"/></td>'+
			'<td>查询页数：<input  type="text" name="select['+index+'][page]"  class="easyui-textbox"  data-options="required:true"/></td>'+
			'<td><input  type="button"  value="删除" onclick="delete_query(this)"></input></td>'+
		'</tr>';
       $('table').find('tr.query').last().after(str);
       $('input[type="text"]').textbox();
    }
    function delete_query(obj){
        $(obj).parents('tr:first').remove();
    }
		function submitForm(){
			$('#myform').form('submit');
		}
</script>

</body>
</html>






