Imports System.Drawing
Imports System.Text.RegularExpressions
Imports System.Windows.Forms
Imports System.Windows.Input
Imports Microsoft.VisualStudio.TestTools.UITest.Extension
Imports Microsoft.VisualStudio.TestTools.UITesting
Imports Microsoft.VisualStudio.TestTools.UITesting.Keyboard
Imports Microsoft.VisualStudio.TestTools.UnitTesting

<CodedUITest()>
Public Class CodedUITest1

    <TestMethod()>
    Public Sub systemTest_add()
        '            
        ' To generate code for this test, select "Generate Code for Coded UI Test" from the shortcut menu and select one of the menu items.
        '
        Me.UIMap.add_details_time_date_impt()
        Me.UIMap.assert_add_details_time_date_impt()

    End Sub
    <TestMethod()>
    Public Sub systemTest_delete_home()
        '            
        ' To generate code for this test, select "Generate Code for Coded UI Test" from the shortcut menu and select one of the menu items.
        '
        Me.UIMap.delete_test_in_home()
        Me.UIMap.assert_delete_test_in_home()

    End Sub
#Region "Additional test attributes"
        '
        ' You can use the following additional attributes as you write your tests:
        '
        '' Use TestInitialize to run code before running each test
        '<TestInitialize()> Public Sub MyTestInitialize()
        '    '
        '    ' To generate code for this test, select "Generate Code for Coded UI Test" from the shortcut menu and select one of the menu items.
        '    '
        'End Sub

        '' Use TestCleanup to run code after each test has run
        '<TestCleanup()> Public Sub MyTestCleanup()
        '    '
        '    ' To generate code for this test, select "Generate Code for Coded UI Test" from the shortcut menu and select one of the menu items.
        '    '
        'End Sub

#End Region

        '''<summary>
        '''Gets or sets the test context which provides
        '''information about and functionality for the current test run.
        '''</summary>
        Public Property TestContext() As TestContext
            Get
                Return testContextInstance
            End Get
            Set(ByVal value As TestContext)
                testContextInstance = Value
            End Set
        End Property

        Private testContextInstance As TestContext

    Public ReadOnly Property UIMap As SystemTestGUI.UIMap
        Get
            If (Me.map Is Nothing) Then
                Me.map = New SystemTestGUI.UIMap()
            End If

            Return Me.map
        End Get
    End Property
    Private map As SystemTestGUI.UIMap
End Class
