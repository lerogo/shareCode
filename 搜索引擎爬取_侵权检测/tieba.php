<?php
header("Content-type: text/html; charset=utf-8");
error_reporting(1);
set_time_limit(6000);

if (!empty($_POST)) {
    $keyword = $_POST['keyword'];
    $backlist = $_POST['backlist'];
    $backlists = array();
    if($backlist !=''){
            $backlists = explode('|', $backlist);
    }
    
    $page = $_POST['page'];
    $query = $_POST['query'];
  
    $sheets = array();
    $total = 1;
    for ($i = 0; $i < $page; $i ++) {
        $data = ''; 
        //$keyword = mb_convert_encoding($data, 'gbk','utf8');
        $url = 'http://tieba.baidu.com/f/search/res?ie=utf-8&qw=' . urlencode($keyword) .'&pn='.$i. '&' . $query;     
        $data = file_get_contents($url);
        //print_r($data);die;
        // 获取含有需要内容div
        $data = preg_replace("/[\t\n\r]+/", "", $data); 
        $data = mb_convert_encoding($data, 'utf8','gbk');
       // print_r($data);die;
        preg_match_all("/<div class=\"s_post\">(.*)class=\"p_green p_date\"/iU", $data, $divs);
      // print_r($divs);die;
        // 进一步获取URL和作者
        foreach ($divs[0] as $div) {
            $link = $desc = $title = '';
            preg_match("/该贴子已删除/iU", $div, $deletes);
            //print_r($deletes);
            if(isset($deletes[0])&&!empty($deletes[0])){
                continue;
            }
            preg_match("/class=\"bluelink\" href=\"(.*)\" class=\"bluelink\" target=\"_blank\" >(.*)<\/a><\/span>/iU", $div, $links);
            preg_match("/<div class=\"p_content\">(.*)<\/div>/iU", $div, $descs);

            preg_match("/<a data-fid(.*)<\/font><\/a>/iU", $div, $tieba);
            preg_match("/作者：<a href(.*)<\/font><\/a>/iU", $div, $author);
            

            //print_r($tiebaword);die;
            if(!empty($links)){
                    $link = $links[1];
                    $title = strip_tags($links[2]);
                    $desc =$descs[1];
                    //$tiebaword = ltrim(strip_tags($tieba[0]),'贴吧：');
                    $tiebaword = ltrim(strip_tags($tieba[0]),'');
                    $authorword = ltrim(strip_tags($author[0]),'作者：');
            }
           
                  
            // 如果标题包含黑名单，如果内容包含链接
            $flag = true;  
            if(!empty($backlists)){
                    foreach ($backlists as $backlist) {
                            if (strpos($desc, trim($backlist)) !== false) {
                                    $flag = false;
                            }
                    }   
            }
            
             // if(!preg_match("/((http|ftp|https|thunder):\/\/)([a-zA-Z0-9_-]+\.)*/", $desc)){
              //       $flag = false;
            // } 
            if ($flag) {            
                $sheets[$total]['keyword'] = $keyword;
                $sheets[$total]['author'] = $authorword;
                $sheets[$total]['url'] = $link;
                $sheets[$total]['title'] = $title;
                $sheets[$total]['p_violet'] = $link;
                $sheets[$total]['tieba'] = $tiebaword;
                $sheets[$total]['desc'] = strip_tags($desc);
                $total ++;
            }
           
        }
        
    }
    //print_r($sheets);die;
    /**
     * ***************************************************导出excel***************************************************
     */
    require_once 'PHPExcel/Classes/PHPExcel.php';
    require_once 'PHPExcel/Classes/PHPExcel/IOFactory.php';
    $objPHPExcel = new PHPExcel();
    /* 设置单元格的标题 */
    $objPHPExcel->setActiveSheetIndex(0)->mergeCells('A1:G1'); // 合并单元格
    $objPHPExcel->setActiveSheetIndex(0)->setCellValue('A1', '百度贴吧侵权监测结果');
    // 设置font
    $objPHPExcel->setActiveSheetIndex(0)->getStyle('A1') ->getFont()->setSize(14);
    $objPHPExcel->setActiveSheetIndex(0)->getStyle('A1')->getFont() ->setBold(true);
    $objPHPExcel->setActiveSheetIndex(0)->getStyle('A1')->getFont()->getColor()->setARGB(PHPExcel_Style_Color::COLOR_BLACK);
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
    $objPHPExcel->setActiveSheetIndex(0)->getColumnDimension('A')->setWidth(10); // 表示设置A这一列的宽度,以下一样
    $objPHPExcel->setActiveSheetIndex(0)->getColumnDimension('B')->setWidth(10);
    $objPHPExcel->setActiveSheetIndex(0)->getColumnDimension('C')->setWidth(20);
    $objPHPExcel->setActiveSheetIndex(0)->getColumnDimension('D')->setWidth(15);
    $objPHPExcel->setActiveSheetIndex(0)->getColumnDimension('E')->setWidth(10);
    $objPHPExcel->setActiveSheetIndex(0)->getColumnDimension('F') ->setWidth(10);
    $objPHPExcel->setActiveSheetIndex(0)->getColumnDimension('G')->setWidth(60);
    $objPHPExcel->setActiveSheetIndex(0)->getColumnDimension('H')->setWidth(30);
    $objPHPExcel->setActiveSheetIndex(0)->getColumnDimension('I')->setWidth(80);
    
    $objPHPExcel->setActiveSheetIndex(0)->setCellValue('A2', '作品名称');
    $objPHPExcel->setActiveSheetIndex(0)->setCellValue('B2', '平台');
    $objPHPExcel->setActiveSheetIndex(0)->setCellValue('C2', '链接网址');
    $objPHPExcel->setActiveSheetIndex(0)->setCellValue('D2', '用户名');
    $objPHPExcel->setActiveSheetIndex(0)->setCellValue('E2', '发函情况');
    $objPHPExcel->setActiveSheetIndex(0)->setCellValue('F2', '处理结果');
    $objPHPExcel->setActiveSheetIndex(0)->setCellValue('G2', '标题');
    $objPHPExcel->setActiveSheetIndex(0)->setCellValue('H2', '贴吧');
    $objPHPExcel->setActiveSheetIndex(0)->setCellValue('I2', '内容');
    
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
    
    if (! empty($sheets)) {
        $k = 3;
        foreach ($sheets as $sheet) {
            $objPHPExcel->setActiveSheetIndex(0)->setCellValue('A'.$k, $sheet['keyword']);
            $objPHPExcel->setActiveSheetIndex(0)->setCellValue('B' . $k, '百度贴吧');
            $objPHPExcel->setActiveSheetIndex(0)->setCellValue('C' . $k, 'http://tieba.baidu.com'.$sheet['url']);
            //$objPHPExcel->setActiveSheetIndex(0)->setCellValue('D' . $k, 'p_violet');
            $objPHPExcel->setActiveSheetIndex(0)->setCellValue('D' . $k, $sheet['author']);
            $objPHPExcel->setActiveSheetIndex(0)->setCellValue('E' . $k, date('y.m.d') . ' 邮件');
            $objPHPExcel->setActiveSheetIndex(0)->setCellValue('F' . $k, '待处理');
            $objPHPExcel->setActiveSheetIndex(0)->setCellValue('G'.$k, $sheet['title']);
            $objPHPExcel->setActiveSheetIndex(0)->setCellValue('H'.$k, $sheet['tieba']);
            $objPHPExcel->setActiveSheetIndex(0)->setCellValue('I' . $k, $sheet['desc']);
            
            $objPHPExcel->getActiveSheet()
                ->getStyle('F' . $k)
                ->getFill()
                ->setFillType(PHPExcel_Style_Fill::FILL_SOLID);
            $objPHPExcel->getActiveSheet()
                ->getStyle('F' . $k)
                ->getFill()
                ->getStartColor()
                ->setARGB(PHPExcel_Style_Color::COLOR_YELLOW);
            $objPHPExcel->setActiveSheetIndex(0)
                ->getStyle('A' . $k . ':F' . $k)
                ->applyFromArray($styleArray);
            $k ++;
        }
    }
    
    $objPHPExcel->getActiveSheet()->setTitle('论坛');
    $objPHPExcel->setActiveSheetIndex(0);
    $objWriter = PHPExcel_IOFactory::createWriter($objPHPExcel, 'Excel5');
    header("Content-Disposition:attachment;filename=" . date('y.m.d') . "-百度贴吧   侵权链接监测结果.xls");
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
<meta http-equiv="Content-Type" content="text/html;charset=UTF-8">
<form method="post" action="" enctype="multipart/form-data">
	<center>
		<h3>百度贴吧侵权链接搜集系统</h3>
	</center>
	<center>
		<h5 style="color:red">注意：标题黑名单可不设</h5>
	</center>
	<center>
		查询关键字：<input type="text" name="keyword" size="20 " />&nbsp;&nbsp;&nbsp;&nbsp;
		查询页数：<input type="text" name="page" />&nbsp;&nbsp;&nbsp;&nbsp;
	</center>
	<br>
	<center>
		标题黑名单(多个以|隔开)：<input type="text" name="backlist"
		value="权利|权力" />&nbsp;&nbsp;&nbsp;&nbsp;
	</center>
	<br>
	<center>
		

	 排序方式：<select name="query">
			<option value="sm=1">按时间倒序</option>
			<option value="sm=0">按时间顺序</option>
			<option value="sm=2">按相关性</option>
			<option value="sm=1&only_thread=1">只看主题帖</option>
		</select> <input type="submit" value="收集" />
	</center>
</form>








