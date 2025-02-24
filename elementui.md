Element UI 提供了以下几种布局组件

**1. Container 布局容器**

   用于快速搭建页面的基本结构：

   *   `<el-container>`：外层容器。
        *   当子元素中包含 `<el-header>` 或 `<el-footer>` 时，全部子元素会垂直上下排列。
        *   否则，子元素会水平从左到右排列。
   *   `<el-header>`：顶栏容器。
   *   `<el-aside>`：侧边栏容器。
   *   `<el-main>`：主要区域容器。
   *   `<el-footer>`：底栏容器。

   ```html
   <el-container>
     <el-header>Header</el-header>
     <el-aside width="200px">Aside</el-aside>
     <el-container>
       <el-main>Main</el-main>
       <el-footer>Footer</el-footer>
     </el-container>
   </el-container>
   ````

**2. Row 和 Col 栅格布局**

   基于 24 栅格系统，通过 `<el-row>` 和 `<el-col>` 组件进行灵活的布局：

   *   `<el-row>`：行组件，可以设置 `gutter` 属性来指定列之间的间距。
   *   `<el-col>`：列组件，通过 `span` 属性指定占据的列数。
      *   可以使用 `offset` 属性设置列的偏移量。
      *   支持响应式布局，通过 `xs`、`sm`、`md`、`lg`、`xl` 属性设置不同屏幕尺寸下的列数。

   ```html
   <el-row :gutter="20">
     <el-col :span="6"><div class="grid-content"></div></el-col>
     <el-col :span="6"><div class="grid-content"></div></el-col>
     <el-col :span="6"><div class="grid-content"></div></el-col>
     <el-col :span="6"><div class="grid-content"></div></el-col>
   </el-row>
   ````

   ```html
    <el-row>
       <el-col :span="12" :offset="6"><div class="grid-content"></div></el-col>
    </el-row>
   ````

**3. Divider 分割线**

   `<el-divider>` 组件用于分隔内容：
    *   可以设置 `direction` 属性为 `vertical` 来使用垂直分割线。
    *   可以通过插槽自定义分割线中间的内容。


 Element UI 里的各种“部件”

**1. 基础组件 (Basic)**

   这些组件是最常用的，用于构建页面的基本元素：

   *   **Button 按钮 (`<el-button>`)**: 用于触发操作。
   *   **Icon 图标 (`<el-icon>`)**: 提供了一套常用的图标。
   *   **Link 链接 (`<el-link>`)**: 用于页面跳转。
   *   **Container 布局容器** (已详细介绍过)
   *   **Row/Col 栅格布局** (已详细介绍过)
   *   **Divider 分割线**

**2. 表单组件 (Form)**

   用于构建各种表单，收集用户信息：

   *   **Input 输入框 (`<el-input>`)**: 用于输入文本、数字等。
   *   **InputNumber 计数器 (`<el-input-number>`)**: 用于输入数字，并提供加减按钮。
   *   **Select 选择器 (`<el-select>`)**: 用于从下拉列表中选择。
   *   **Cascader 级联选择器 (`<el-cascader>`)**: 用于选择多级关联的数据。
   *   **Checkbox 多选框 (`<el-checkbox>`)**: 用于选择多个选项。
   *   **Radio 单选框 (`<el-radio>`)**: 用于选择一个选项。
   *   **Switch 开关 (`<el-switch>`)**: 用于在两种状态之间切换。
   *   **Slider 滑块 (`<el-slider>`)**: 用于通过滑动选择数值。
   *   **TimePicker 时间选择器 (`<el-time-picker>`)**: 用于选择时间。
   *   **DatePicker 日期选择器 (`<el-date-picker>`)**: 用于选择日期。
   *   **DateTimePicker 日期时间选择器 (`<el-date-time-picker>`)**: 用于选择日期和时间。
   *   **Upload 上传 (`<el-upload>`)**: 用于上传文件。
   *   **Rate 评分 (`<el-rate>`)**: 用于评分。
   *   **ColorPicker 颜色选择器 (`<el-color-picker>`)**: 用于选择颜色。
   *   **Transfer 穿梭框 (`<el-transfer>`)**: 用于在两个列表之间移动数据。
   *   **Form 表单 (`<el-form>`)**: 用于包裹表单组件，提供表单验证功能。

**3. 数据展示组件 (Data)**

   用于展示数据：

   *   **Table 表格 (`<el-table>`)**: 用于展示结构化数据。
   *   **Tag 标签 (`<el-tag>`)**: 用于标记和分类。
   *   **Progress 进度条 (`<el-progress>`)**: 用于显示操作的进度。
   *   **Tree 树形控件 (`<el-tree>`)**: 用于展示层级结构的数据。
   *   **Pagination 分页 (`<el-pagination>`)**: 用于分页显示大量数据。
   *   **Badge 标记 (`<el-badge>`)**: 用于在右上角显示标记。
   *   **Avatar 头像 (`<el-avatar>`)**: 用于显示用户头像。
   *   **Empty 空状态 (`<el-empty>`)**: 用于在没有数据时显示。

**4. 通知组件 (Notice)**

   用于显示通知信息：

   *   **Alert 警告 (`<el-alert>`)**: 用于显示警告信息。
   *   **Loading 加载 (`<el-loading>`)**: 用于显示加载状态。
   *   **Message 消息提示 (`<el-message>`)**: 用于显示全局的消息提示。
   *   **MessageBox 弹框 (`<el-message-box>`)**: 用于显示模态对话框。
   *   **Notification 通知 (`<el-notification>`)**: 用于显示右上角的通知。

**5. 导航组件 (Navigation)**

   用于构建导航菜单：

   *   **Menu 菜单 (`<el-menu>`)**: 用于构建垂直或水平的菜单。
   *   **Tabs 标签页 (`<el-tabs>`)**: 用于在多个视图之间切换。
   *   **Breadcrumb 面包屑 (`<el-breadcrumb>`)**: 用于显示当前页面的路径。
   *   **PageHeader 页头 (`<el-page-header>`)**: 用于返回上一级页面。
   *   **Dropdown 下拉菜单 (`<el-dropdown>`)**: 用于显示下拉菜单。
   *   **Steps 步骤条 (`<el-steps>`)**: 用于引导用户完成流程。

**6. 其他组件 (Others)**

   *   **Dialog 对话框 (`<el-dialog>`)**: 用于显示模态对话框。
   *   **Tooltip 文字提示 (`<el-tooltip>`)**: 用于显示文字提示。
   *   **Popover 弹出框 (`<el-popover>`)**: 用于显示弹出框。
   *   **Popconfirm 气泡确认框 (`<el-popconfirm>`)**: 用于显示气泡确认框。
   *   **Card 卡片 (`<el-card>`)**: 用于将内容包裹在卡片中。
   *   **Carousel 走马灯 (`<el-carousel>`)**: 用于轮播图片或内容。
   *   **Collapse 折叠面板 (`<el-collapse>`)**: 用于折叠内容。
   *   **Timeline 时间线 (`<el-timeline>`)**: 用于显示时间线。
   *   **Calendar 日历 (`<el-calendar>`)**: 用于显示日历。
   *   **Image 图片 (`<el-image>`)**: 用于显示图片，支持懒加载。
   *   **Backtop 回到顶部 (`<el-backtop>`)**: 用于返回页面顶部。
   *   **InfiniteScroll 无限滚动 (`<el-infinite-scroll>`)**: 用于无限滚动加载数据。
   *   **Drawer 抽屉 (`<el-drawer>`)**: 用于从侧边滑出抽屉。

Element UI 的官方文档来查看所有组件的详细用法和示例：[https://element.eleme.cn/](https://element.eleme.cn/)

