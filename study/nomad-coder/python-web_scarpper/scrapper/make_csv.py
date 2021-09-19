import csv

def filename_valid_check(filename):
  replace_bar=['\\','/',':','<','>','|','"','?','*']
  for ele in replace_bar:
    filename=filename.replace(ele,'-')
  return filename

def make_csv_dict_in_list(dict_in_list,filename="no_name"):
  filename=filename_valid_check(filename)
  file=open(f'{filename}.csv',mode='w')
  writer=csv.writer(file)
  if dict_in_list:
    writer.writerow(dict_in_list[0].keys())
    for dict in dict_in_list:
      writer.writerow(dict.values())
  else:
    writer.writerow(["there's no data in dict_in_list"])
  file.close()