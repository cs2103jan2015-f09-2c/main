Imports Microsoft.VisualStudio.TestTools.UITesting.WinControls
Imports System
Imports System.Collections.Generic
Imports System.CodeDom.Compiler
Imports Microsoft.VisualStudio.TestTools.UITest.Extension
Imports Microsoft.VisualStudio.TestTools.UITesting
Imports Microsoft.VisualStudio.TestTools.UnitTesting
Imports Keyboard = Microsoft.VisualStudio.TestTools.UITesting.Keyboard
Imports Mouse = Microsoft.VisualStudio.TestTools.UITesting.Mouse
Imports MouseButtons = System.Windows.Forms.MouseButtons
Imports System.Drawing
Imports System.Windows.Input
Imports System.Text.RegularExpressions

Namespace SystemTestGUI

    Partial Public Class UIMap

        '''<summary>
        '''Assert for UIMap add_details_time_date_impt
        '''</summary>
        Public Sub assert_add_details_time_date_impt()
            Dim uIDisplayWindowEdit As WinEdit = Me.UIPlanner4LifeWindow.UIDisplayWindowWindow.UIDisplayWindowEdit

            'Verify that the 'Text' property of 'displayWindow' text box equals '1. event a 
            '2. event b Date: 15/4/15 
            '3. event c Date: 15/4/15 to 16/4/15 
            '4. event d Date: 15/4/15 to 16/4/15 Time: 0800 
            '5. event e Date: 15/4/15 to 16/4/15 Time: 0800 to 0900 
            '6. event f Date: 16/4/15 to 17/4/15 Time: 0800 to 0900 #impt
            ''
            Assert.AreEqual(Me.assert_add_details_time_date_imptExpectedValues.UIDisplayWindowEditText, uIDisplayWindowEdit.Text)
        End Sub

        Public Overridable ReadOnly Property assert_add_details_time_date_imptExpectedValues() As assert_add_details_time_date_imptExpectedValues
            Get
                If (Me.massert_add_details_time_date_imptExpectedValues Is Nothing) Then
                    Me.massert_add_details_time_date_imptExpectedValues = New assert_add_details_time_date_imptExpectedValues()
                End If
                Return Me.massert_add_details_time_date_imptExpectedValues
            End Get
        End Property

        Private massert_add_details_time_date_imptExpectedValues As assert_add_details_time_date_imptExpectedValues
    End Class
    '''<summary>
    '''Parameters to be passed into 'assert_add_details_time_date_impt'
    '''</summary>
    <GeneratedCode("Coded UITest Builder", "12.0.31101.0")> _
    Public Class assert_add_details_time_date_imptExpectedValues

#Region "Fields"
        '''<summary>
        '''Verify that the 'Text' property of 'displayWindow' text box equals '1. event a 
        '''2. event b Date: 15/4/15 
        '''3. event c Date: 15/4/15 to 16/4/15 
        '''4. event d Date: 15/4/15 to 16/4/15 Time: 0800 
        '''5. event e Date: 15/4/15 to 16/4/15 Time: 0800 to 0900 
        '''6. event f Date: 16/4/15 to 17/4/15 Time: 0800 to 0900 #impt
        ''''
        '''</summary>
        Public UIDisplayWindowEditText As String = "1. event a " & Global.Microsoft.VisualBasic.ChrW(13) & Global.Microsoft.VisualBasic.ChrW(10) & "2. event b Date: 15/4/15 " & Global.Microsoft.VisualBasic.ChrW(13) & Global.Microsoft.VisualBasic.ChrW(10) & "3. event c Date: 15/4/15 to 16/4/15 " & Global.Microsoft.VisualBasic.ChrW(13) & Global.Microsoft.VisualBasic.ChrW(10) & "4. " & _
            "event d Date: 15/4/15 to 16/4/15 Time: 0800 " & Global.Microsoft.VisualBasic.ChrW(13) & Global.Microsoft.VisualBasic.ChrW(10) & "5. event e Date: 15/4/15 to 16/4/1" & _
            "5 Time: 0800 to 0900 " & Global.Microsoft.VisualBasic.ChrW(13) & Global.Microsoft.VisualBasic.ChrW(10) & "6. event f Date: 16/4/15 to 17/4/15 Time: 0800 to 0900 #i" & _
            "mpt" & Global.Microsoft.VisualBasic.ChrW(13) & Global.Microsoft.VisualBasic.ChrW(10)
#End Region
    End Class
End Namespace
