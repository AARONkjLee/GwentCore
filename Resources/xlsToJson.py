# To run this python 2.x script, please use pip to install xlrd.


import xlrd  
import json  
import codecs  
import os  
  
#把excel表格中指定sheet转为json  
def Excel2Json(file_path):  
    #打开excel文件  
        book = get_data(file_path)  
        #抓取所有sheet页的名称  
        worksheets = book.sheet_names()  
        print "该Excel包含的表单列表为：\n"  
        for sheet in worksheets:  
            print ('%s,%s' %(worksheets.index(sheet),sheet))  
        inp = raw_input('请输入表单名对应的编号，对应表单将自动转为json:\n')  
        sheet = book.sheet_by_index(int(inp))  
        row_0 = sheet.row(0)     #第一行是表单标题  
        nrows=sheet.nrows       #行号  
        ncols=sheet.ncols       #列号  


        result={}   #定义json对象  
        result["title"]=file_path   #表单标题  
        result["rows"]=nrows        #行号  
        result=[]      #每一行作为数组的一项  
        #遍历所有行，将excel转化为json对象  
        for i in range(nrows):  
            if i==0:  
                continue  
            tmp={}  
            #遍历当前行所有列  
            for j in range(ncols):  
                #获取当前列中文标题  
                title_de=str(row_0[j]).decode('unicode_escape')  
                title_cn= title_de.split("'")[1]  
                #获取单元格的值
                if title_cn == "EffectType":
                    tmp_effects = []
                    effects = sheet.row_values(i)[j].replace(" ","").split(",")
                    for effect in effects:
                            tmp_effects.append(effect)
                    tmp["EffectType"]=tmp_effects
                else:
                    temp = (sheet.row_values(i)[j])
                    try:
                        tmp[title_cn]=int(temp) 
                    except(ValueError):
                        if title_cn != "Description" and title_cn != "Pic" and title_cn != "Name":  # 名字，描述和图片文件名不需要删除空格
                                temp = temp.replace(" ","")
                        tmp[title_cn]= temp
            result.append(tmp)  
        json_data=json.dumps(result,indent= 4,sort_keys=True).decode('unicode_escape')  
        file_name = file_path.split(".")[0]  
        saveFile(os.getcwd(),file_name,json_data)  
        print json_data
        print "Successfully create .json file"
  
  
 # 获取excel数据源  
def get_data(file_path):  
     """获取excel数据源"""  
     try:  
         data = xlrd.open_workbook(file_path)  
         return data  
     except Exception, e:  
         print 'excel表格读取失败：%s' %e  
         return None  
  
def saveFile(file_path,file_name,data):  
    output = codecs.open(file_path+"/"+file_name+".json",'w',"utf-8")  
    output.write(data)  
    output.close()  
  
if __name__ == '__main__':
	while 1:
		choice = raw_input('请选择需要转换的数据文件：\n A. 卡池数据（CardPoolDatabase.xlsx）\tB. 领导派数据（LeaderCardPoolDatabase.xlsx)\tC. Exit\n')
		if choice == "A" :
			json_data=Excel2Json("CardPoolDatabase.xlsx")
		elif choice == "B":
			json_data=Excel2Json("LeaderCardPoolDatabase.xlsx")
		elif choice == "C":
			break
		else:
			print "Invalid Input, Try Again."
	
