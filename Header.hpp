# pragma once

class Header{
	private:
		int availList;
		int size;
		bool dirtyBit;
		int recordCount;

	public:
		Header();
		Header(long int availList,int sizeofRegistry,int RecordCount,bool DirtyBit);
		void setAvailList(long int availList);
		void setSize(int size);
		void setDirty(bool Dirty);
		void setRecordCount(int RecordCount);

		long int getAvailList();
		int getSize();
		bool getDirty();
		int getRecordCount();
};