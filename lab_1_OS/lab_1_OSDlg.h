
// lab_1_OSDlg.h : header file
//

#pragma once
#define WM_UPDATE_PROGRESS (WM_USER + 1)


// Clab1OSDlg dialog
class Clab1OSDlg : public CDialogEx
{
// Construction
public:
	Clab1OSDlg(CWnd* pParent = nullptr);	// standard constructor

// Dialog Data
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_LAB_1_OS_DIALOG };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support


// Implementation
protected:
	HICON m_hIcon;

	// Generated message map functions
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
public:

	afx_msg LRESULT OnUpdateProgress(WPARAM wParam, LPARAM lParam);
	int m_selectedThread;
	afx_msg void OnLbnSelchangeList1();
	afx_msg void OnBnClickedMfclink1();
	afx_msg void OnNMCustomdrawProgress2(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void OnBnClickedCheck3();
	afx_msg void OnBnClickedCheck1();
	afx_msg void OnLbnSelchangeList2();
	afx_msg void OnCbnSelchangeComboboxex2();
	afx_msg void OnNMCustomdrawProgress3(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void OnEnChangeEdit2();
	afx_msg void OnLbnSelchangeList4();
	afx_msg void OnBnClickedCreate();
	LRESULT OnNMCustomdrawProgress1(WPARAM wParam, LPARAM lParam);
	CProgressCtrl progres_1;
	afx_msg void OnNMCustomdrawProgress1(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void OnCbnSelchangeComboboxex3();
	afx_msg void OnBnClickedButtonstart();
	
	afx_msg void OnBnClickedButtonStartThread();
	CProgressCtrl progres_2;
	CProgressCtrl progres_3;
	
	afx_msg void OnNMCustomdrawProgress8(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void OnBnClickedButtonStopTheard();
	afx_msg void OnBnClickedButtonTerminateThread();
	afx_msg void OnBnClickedButton11();
	afx_msg void OnLbnSelchangeList5();
	
	CListBox m_CONTEX_WORK;
	CListBox b_Time1;
	CListBox b_Time2;
	
	CListBox b_Time3;
	afx_msg void OnLbnSelchangeList6();
	afx_msg void OnLbnSelchangeList13();
	CComboBox Drop_List;
	afx_msg void OnCbnSelchangeCombo1();
	afx_msg void OnBnClickedButton6();
	afx_msg void OnBnClickedButton7();
	afx_msg void OnBnClickedRadio1();
	afx_msg void OnBnClickedRadio2();
	afx_msg void OnBnClickedRadio3();
	CButton b_RADIO_1;
	afx_msg void OnBnClickedButton8();
};
