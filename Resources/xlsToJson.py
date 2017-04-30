  
import xlrd  
import json  
import codecs  
import os  
  
#��excel�����ָ��sheetתΪjson  
def Excel2Json(file_path):  
    #��excel�ļ�  
    if get_data(file_path) is not None:  
        book = get_data(file_path)  
        #ץȡ����sheetҳ������  
        worksheets = book.sheet_names()  
        print "��Excel�����ı��б�Ϊ��\n"  
        for sheet in worksheets:  
            print ('%s,%s' %(worksheets.index(sheet),sheet))  
        inp = raw_input(u'�����������Ӧ�ı�ţ���Ӧ�����Զ�תΪjson:\n')  
        sheet = book.sheet_by_index(int(inp))  
        row_0 = sheet.row(0)     #��һ���Ǳ�����  
        nrows=sheet.nrows       #�к�  
        ncols=sheet.ncols       #�к�  
  
  
        result={}   #����json����  
        result["title"]=file_path   #������  
        result["rows"]=nrows        #�к�  
        result["children"]=[]      #ÿһ����Ϊ�����һ��  
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
                tmp[title_cn]=sheet.row_values(i)[j]  
            result["children"].append(tmp)  
        json_data=json.dumps(result,indent= 4,sort_keys=True).decode('unicode_escape')  
          
        saveFile(os.getcwd(),worksheets[int(inp)],json_data)  
        print json_data  
  
  
# ��ȡexcel����Դ  
def get_data(file_path):  
    """��ȡexcel����Դ"""  
    try:  
        data = xlrd.open_workbook(file_path)  
        return data  
    except Exception, e:  
        print u'excel����ȡʧ�ܣ�%s' %e  
        return None  
  
def saveFile(file_path,file_name,data):  
    output = codecs.open(file_path+"/"+file_name+".json",'w',"utf-8")  
    output.write(data)  
    output.close()  
  
if __name__ == '__main__':  
    file_path = raw_input(u'������excel�ļ�·����\n')  
    json_data=Excel2Json(file_path)  