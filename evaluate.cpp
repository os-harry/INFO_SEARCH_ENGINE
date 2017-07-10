#include "evaluate.h"

EVL::PLN::PLN()
{
	next = pre = NULL;
	diff = num = 0;
}

EVL::Node::Node()
{
	snum = sum = 0;
	dtl = NULL;
}

bool EVL::Blank(const char x)
{
	return (x==' '||x=='\n');
}

void EVL::Add(const std::string &atcl, LL &i)
{
	while (EVL::Blank(atcl[i])) ++i;
}

std::string EVL::To_String(LL x)
{
	char ch;
	std::string tmp;
	tmp = "";
	if (x==0)	tmp += '0';
	while (x>0)
	{
		tmp += x%10+'0';
		x /= 10;
	}
	for (LL i=0; (unsigned)i<tmp.size()/2; ++i)
	{
		ch = tmp[i];
		tmp[i] = tmp[tmp.size()-1-i];
		tmp[tmp.size()-1-i] = ch;
	}
	return tmp;
}

void EVL::Input_Query(const std::string &fquery,std::map<std::string, Node*> &query,LL &sum_query, THULAC &lac)
{
	using namespace EVL;
	using namespace std;

	string word;
	THULAC_result res;
	LL invalid = 0;

	query.clear();
	sum_query = 0;

	lac.cut(fquery,res);
	for (vector<pair<string,string> >::iterator i=res.begin(); i!=res.end(); ++i)
		if (i->first==" "||i->first=="\n"||i->first=="，"||i->first=="。")
		{
			++invalid;
			continue;
		}
		else if (query.find(i->first)!=query.end())
			query[i->first]->sum += 1;
		else
		{
			query[i->first] = new Node;
			query[i->first]->sum += 1;
		}
	sum_query = res.size()-invalid;
}

void EVL::Count(std::map<std::string,Node*> &dic, double deno_t[EVL::MAX_SIZE], double nume_t[EVL::MAX_SIZE], const string word, double nume_q, const LL sum_text)
{
	using namespace EVL;
	if (dic.find(word)==dic.end())	return;

	LL cnt = dic[word]->snum;
	PLN *p = dic[word]->dtl;
	double tmp_t;

	while (p!=NULL)
	{
		tmp_t = (1+log(p->num)/log(10)) * (log(sum_text*1.0/dic[word]->sum)/log(10));
		nume_t[cnt] += nume_q*tmp_t;
		deno_t[cnt] += dic[word]->sum*dic[word]->sum;
		cnt -= p->diff;
		p = p->pre;
	}
	nume_t[cnt] += nume_q*tmp_t;
	deno_t[cnt] += dic[word]->sum*dic[word]->sum;
}

void EVL::Evaluate(const std::string &fquery, std::map<std::string,Node*>&dic, std::vector<LL> &ans_list, LL &ans_num, const LL sum_text, THULAC &lac)
{
	using namespace std;
	using namespace EVL;

	map<string,Node*>::iterator q_it;
	map<string,Node*> query;
	vector<pair<double,LL> > score;
	double deno_t[MAX_SIZE], nume_t[MAX_SIZE];
	double deno_q, nume, tmp_q;
	LL sum_query,cnt;

	query.clear();
	for (LL i=0; i<MAX_SIZE; ++i)
		deno_t[i] = nume_t[i] = 0;
	deno_q = nume = cnt = 0;

	Input_Query(fquery,query,sum_query,lac);

	for (q_it = query.begin(); q_it!=query.end(); ++q_it,++cnt)
	{
		tmp_q = (1+log(q_it->second->sum)/log(10)) * (log(sum_query/q_it->second->sum)/log(10));
		if (tmp_q==0 && sum_query==1)	tmp_q = 1+log(q_it->second->sum)/log(10);
		deno_q += tmp_q*tmp_q;
		Count(dic,deno_t,nume_t,q_it->first,tmp_q,sum_text);
	}
	score.clear();
	ans_list.clear();
	for (LL i=1; i<MAX_SIZE; ++i)
		if (nume_t[i]!=0 && deno_t[i]!=0)
			score.pb( mp( -nume_t[i]*1.00 / (sqrt(deno_q)*sqrt(deno_t[i])), i ) );
	sort(score.begin(),score.end());

	ans_num = score.size();
	for (LL i=0; i<ans_num && i<10; ++i)
		ans_list.pb(score[i].second);
}

int main()
{
	using namespace EVL;
	using namespace std;

	map<string, Node*> dic,query;
	vector<LL> list_res;
	LL sum_text, num_res, snum, sum, x, y, t1, t2;
	string word;
	PLN *temp,*pp;
	FILE *fquery, *fdic;
	ifstream f_dic, f_query;
	THULAC lac;

	lac.init("models/", NULL, true, 0, 0);
	f_dic.open("dictionary.txt");
	while (f_dic>>word>>snum>>sum)
	{
		dic[word] = new Node;
		dic[word]->snum = snum;
		dic[word]->sum = sum;
		temp = new PLN;
		dic[word]->dtl = temp;
		sum_text += sum;
		pp = NULL;
		while (f_dic>>x>>y)
		{
			if (x==-1 && y==-1)	break;
			temp->diff = x;
			temp->num = y;
			if (pp!=NULL)	pp->pre = temp;
			pp = temp;
			temp = new PLN;
		}
	}
	f_dic.close();
	cout<<"Dictionary loaded succeed.\n";

	while (1)
	{
		f_query.open("E:/Apache2/htdocs/temp1.in");
		if (!f_query.is_open())
		{
			_sleep(100);
			continue;
		}
		t1 = clock();
		getline(f_query,str_q);
		f_query.close();

		Evaluate(str_q,dic,list_res,num_res,sum_text,lac);
		fquery = fopen("E:/Apache2/htdocs/answer_list.out","w");
		fprintf(fquery,"%d\n",num_res);
		for (int i=0; i<10 && i<num_res; ++i)
			fprintf(fquery,"%d\n",list_res[i]);
		fclose(fquery);
		t2 = clock();
		cout<<t2-t1<<endl;
		_sleep(200);
		remove("E:/Apache2/htdocs/answer_list.out");
		_sleep(1000);
	}

	fclose(stdout);

	return 0;
}
