# pragma once

class Header{
	private:
		int availList;
		int size;
		bool dirtyBit;
		int recordCount;

	public:
		Header(int availList,int sizeOfCampo,int RecordCount,bool DirtyBit);
		void setAvailList(int availList);
		void setSize(int size);
		void setDirty(bool Dirty);
		void setRecordCount(int RecordCount);

		int getAvailList();
		int getSize();
		bool getDirty();
		int getRecordCount();
};