# To run this python 2.x script, please use pip to install xlrd.


import xlrd  
import json  
import codecs  
import os  
  
#��excel�����ָ��sheetתΪjson  
def Excel2Json(file_path):  
    #��excel�ļ�  
        book = get_data(file_path)  
        #ץȡ����sheetҳ������  
        worksheets = book.sheet_names()  
        print "��Excel�����ı��б�Ϊ��\n"  
        for sheet in worksheets:  
            print ('%s,%s' %(worksheets.index(sheet),sheet))  
        inp = raw_input('�����������Ӧ�ı�ţ���Ӧ�����Զ�תΪjson:\n')  
        sheet = book.sheet_by_index(int(inp))  
        row_0 = sheet.row(0)     #��һ���Ǳ�����  
        nrows=sheet.nrows       #�к�  
        ncols=sheet.ncols       #�к�  


        result={}   #����json����  
        result["title"]=file_path   #������  
        result["rows"]=nrows        #�к�  
        result=[]      #ÿһ����Ϊ�����һ��  
        #���������У���excelת��Ϊjson����  
        for i in range(nrows):  
            if i==0:  
                continue  
            tmp={}  
            #������ǰ��������  
            for j in range(ncols):  
                #��ȡ��ǰ�����ı���  
                title_de=str(row_0[j]).decode('unicode_escape')  
                title_cn= title_de.split("'")[1]  
                #��ȡ��Ԫ���ֵ
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
                        if title_cn != "Description" and title_cn != "Pic" and title_cn != "Name":  # ���֣�������ͼƬ�ļ�������Ҫɾ���ո�
                                temp = temp.replace(" ","")
                        tmp[title_cn]= temp
            result.append(tmp)  
        json_data=json.dumps(result,indent= 4,sort_keys=True).decode('unicode_escape')  
        file_name = file_path.split(".")[0]  
        saveFile(os.getcwd(),file_name,json_data)  
        print json_data
        print "Successfully create .json file"
  
  
 # ��ȡexcel����Դ  
def get_data(file_path):  
     """��ȡexcel����Դ"""  
     try:  
         data = xlrd.open_workbook(file_path)  
         return data  
     except Exception, e:  
         print 'excel����ȡʧ�ܣ�%s' %e  
         return None  
  
def saveFile(file_path,file_name,data):  
    output = codecs.open(file_path+"/"+file_name+".json",'w',"utf-8")  
    output.write(data)  
    output.close()  
  
if __name__ == '__main__':
	while 1:
		choice = raw_input('��ѡ����Ҫת���������ļ���\n A. �������ݣ�CardPoolDatabase.xlsx��\tB. �쵼�����ݣ�LeaderCardPoolDatabase.xlsx)\tC. Exit\n')
		if choice == "A" :
			json_data=Excel2Json("CardPoolDatabase.xlsx")
		elif choice == "B":
			json_data=Excel2Json("LeaderCardPoolDatabase.xlsx")
		elif choice == "C":
			break
		else:
			print "Invalid Input, Try Again."
	
